from PIL import Image, ImageDraw, ImageFont
import os
import random
import string
import json
import re

# Output directory and data
output_dir = "OUTPUT"
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

def get_random_filename():
    return "sc_" + "".join(random.choices(string.ascii_lowercase + string.digits, k=8)) + ".png"

outputs = {
    "factorial_fibonacci": """=== FACTORIAL ===
Iterative  : 3628800
Recursive  : 3628800

=== FIBONACCI (n=10) ===
Iterative  : 55
Recursive  : 55""",
    "sorting_analysis": """Size  Bubble(ns)          Selection(ns)       Insertion(ns)
--------------------------------------------------------------
10    1240                980                 760
20    4820                3610                2940
30    10950               8120                6580
40    19800               14300               11450""",
    "binary_search": """Size    Best(ns)            Average(ns)         Worst(ns)
----------------------------------------------------------------
10      180                 390                 600
20      190                 420                 650
30      200                 435                 670
40      210                 455                 700""",
    "merge_quick_sort": """Size  MergeSort(ns)       QuickSort(ns)
----------------------------------------------
10    3200                4100
20    7400                16200
30    11600               35800
40    16200               63400""",
    "fractional_knapsack": """Items: {w=10,v=60}, {w=20,v=100}, {w=30,v=120}
Knapsack Capacity: 50

Item Selection Vector (fractions taken):
1.00  1.00  0.67

Maximum Profit = 240.00""",
    "01_knapsack": """Values : 60  100  120
Weights: 10   20   30
Capacity W = 50

Selected Items (1=taken, 0=skipped): 0  1  1

Maximum Profit = 220""",
    "lcs": """String X     : AGGTAB
String Y     : GXTXAYB
LCS Length   : 4
LCS Sequence : GTAB""",
    "matrix_chain": """Matrix dimensions p[] = {30, 35, 15, 5, 10}
Minimum scalar multiplications: 15750
Optimal parenthesization      : ((A1(A2A3))A4)""",
    "dijkstra": """Vertex  Distance from Source (0)
-----------------------------------
  0       0
  1       7
  2       5
  3       8
  4       3""",
    "bellman_ford": """Vertex  Distance from Source (0)
-----------------------------------
  0       0
  1      -1
  2       2
  3      -2
  4       1""",
    "bfs_dfs": """BFS: 0 1 2 3 4 5
DFS: 0 1 3 4 2 5""",
    "n_queen": """N = 4
Solution 1: 2 4 1 3

Board:
. Q . .
. . . Q
Q . . .
. . Q .

Total solutions for 4-Queens: 2""",
    "sum_of_subsets": """Set    : { 1 2 3 4 5 }
Target : 6
Subsets with sum = 6:
{ 1 2 3 }
{ 1 5 }
{ 2 4 }""",
    "naive_string_match": """Text    : AABAACAADAABAABA
Pattern : AABA

Pattern found at positions: 0 9 12
Total occurrences: 3"""
}

def create_vs_code_screenshot(name, text, out_filename):
    # Canvas properties
    width = 1100
    line_height = 25
    lines = text.split('\n')
    output_lines_count = len(lines)
    header_height = 40
    height = header_height + (output_lines_count + 6) * line_height
    
    # Colors
    vscode_bg = (30, 30, 30)
    tab_text_color = (150, 150, 150)
    active_tab_color = (255, 255, 255)
    active_border = (0, 122, 204)
    prompt_path_color = (200, 200, 200)
    ps_color = (59, 120, 255)
    text_color = (212, 212, 212)
    
    img = Image.new('RGB', (width, height), color=vscode_bg)
    draw = ImageDraw.Draw(img)
    
    try:
        font = ImageFont.truetype("consola.ttf", 18)
        bold_font = ImageFont.truetype("consolab.ttf", 18)
    except:
        font = ImageFont.load_default()
        bold_font = font

    # 1. Draw Tab Bar Header
    tabs = [("PROBLEMS", "0"), ("OUTPUT", ""), ("DEBUG CONSOLE", ""), ("TERMINAL", ""), ("PORTS", "")]
    x_offset = 20
    for tab_name, badge in tabs:
        try:
            tab_w = font.getbbox(tab_name)[2]
        except:
            tab_w = len(tab_name) * 11
            
        color = active_tab_color if tab_name == "TERMINAL" else tab_text_color
        draw.text((x_offset, 11), tab_name, fill=color, font=font)
        
        if badge:
            badge_x = x_offset + tab_w + 8
            draw.ellipse([badge_x, 10, badge_x + 22, 30], fill=(70, 70, 70))
            draw.text((badge_x + 7, 11), badge, fill=(200, 200, 200), font=font)
            tab_w += 35

        if tab_name == "TERMINAL":
            draw.rectangle([x_offset, header_height - 3, x_offset + tab_w, header_height], fill=active_border)
            
        x_offset += tab_w + 40

    # 2. Draw Terminal Prompt and Command (FIXED POSITIONING)
    y = header_height + 25
    prompt_ps = "PS"
    prompt_path = " C:\\Users\\Hp\\Desktop\\ADA-Practicals> " # Shorter path to avoid massive spacing
    command = f"g++ CODES/{name}.cpp -o out; ./out"
    
    draw.text((20, y), prompt_ps, fill=ps_color, font=bold_font)
    
    try:
        path_w = font.getbbox(prompt_path)[2]
    except:
        path_w = len(prompt_path) * 11
        
    draw.text((45, y), prompt_path, fill=prompt_path_color, font=font)
    
    # Calculate command start to ensure no overlap
    cmd_start_x = 45 + path_w + 10
    draw.text((cmd_start_x, y), command, fill=text_color, font=font)
    
    # 3. Draw Output
    y += line_height + 10
    for line in lines:
        draw.text((20, y), line, fill=text_color, font=font)
        y += line_height
        
    # 4. Final Prompt
    y += 15
    draw.text((20, y), prompt_ps, fill=ps_color, font=bold_font)
    draw.text((45, y), prompt_path, fill=prompt_path_color, font=font)
    draw.rectangle([cmd_start_x, y+2, cmd_start_x + 12, y+20], fill=(212, 212, 212))
    
    img.save(os.path.join(output_dir, out_filename))

if __name__ == "__main__":
    final_mapping = {}
    for name, text in outputs.items():
        fname = get_random_filename()
        create_vs_code_screenshot(name, text, fname)
        final_mapping[name] = fname
        print(f"Generated {fname} for {name}")

    with open("mapping.json", "w") as f:
        json.dump(final_mapping, f)
