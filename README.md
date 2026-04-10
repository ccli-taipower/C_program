# EE2310 C 程式設計 參考解答（2025）

NTHU EE2310（2025 年度）《由片語學習C程式設計（第二版）》課程的 C 語言參考解答，依照課本章節分類整理。

## 說明

- 所有程式碼以簡單的 **C 語言**撰寫（不使用 C++ 語法）
- 每個檔案包含詳細的**繁體中文註解**
- 每題說明參考課本章節，方便對應學習
- 每題附有原始題目連結（[NTHU ACM Online Judge](https://acm.cs.nthu.edu.tw/)）

## 編譯方式

```bash
gcc -std=c99 -o out NNNNN.c -lm
```

部分題目需要 `-lm` 連結數學函式庫（如 `sin`、`cos`、`sqrt`）。

---

## 章節索引

### Ch03 — 運算

| 題號 | 題目 | 題目連結 |
|------|------|----------|
| [14651](Ch03_operation/14651_rectangle_perimeter_area/14651.c) | Compute rectangle perimeter and area | [🔗](https://acm.cs.nthu.edu.tw/problem/14651/) |
| [14667](Ch03_operation/14667_rect_area_2d/14667.c) | Rectangle area (2D) | [🔗](https://acm.cs.nthu.edu.tw/problem/14667/) |
| [14668](Ch03_operation/14668_cuboid_surface_volume/14668.c) | Cuboid surface area and volume | [🔗](https://acm.cs.nthu.edu.tw/problem/14668/) |
| [14685](Ch03_operation/14685_sum_four_digit/14685.c) | Sum of digits of a four-digit number | [🔗](https://acm.cs.nthu.edu.tw/problem/14685/) |

### Ch04 — 判斷

| 題號 | 題目 | 題目連結 |
|------|------|----------|
| [14653](Ch04_branch/14653_max_three_integers/14653.c) | Maximum of three integers | [🔗](https://acm.cs.nthu.edu.tw/problem/14653/) |
| [14682](Ch04_branch/14682_line_through_origin/14682.c) | Check if line passes through origin | [🔗](https://acm.cs.nthu.edu.tw/problem/14682/) |
| [14683](Ch04_branch/14683_animals_in_cage/14683.c) | Animals in a cage (chicken & rabbit) | [🔗](https://acm.cs.nthu.edu.tw/problem/14683/) |
| [14684](Ch04_branch/14684_triangle_inequality/14684.c) | Triangle inequality | [🔗](https://acm.cs.nthu.edu.tw/problem/14684/) |
| [14686](Ch04_branch/14686_multiple_determination/14686.c) | Multiple determination | [🔗](https://acm.cs.nthu.edu.tw/problem/14686/) |
| [14688](Ch04_branch/14688_triangle_categories/14688.c) | Triangle categories | [🔗](https://acm.cs.nthu.edu.tw/problem/14688/) |

### Ch05 — 迴圈

| 題號 | 題目 | 題目連結 |
|------|------|----------|
| [14687](Ch05_loop/14687_sum_integers/14687.c) | Sum of integers | [🔗](https://acm.cs.nthu.edu.tw/problem/14687/) |
| [14699](Ch05_loop/14699_calculation_of_days/14699.c) | Calculation of days from 1970-01-01 | [🔗](https://acm.cs.nthu.edu.tw/problem/14699/) |
| [14700](Ch05_loop/14700_carry_system_conversion/14700.c) | Number base conversion (2/8/10) | [🔗](https://acm.cs.nthu.edu.tw/problem/14700/) |
| [14706](Ch05_loop/14706_digit_rotation/14706.c) | Digit rotation | [🔗](https://acm.cs.nthu.edu.tw/problem/14706/) |
| [14715](Ch05_loop/14715_prime_factorization/14715.c) | Prime factorization | [🔗](https://acm.cs.nthu.edu.tw/problem/14715/) |
| [14743](Ch05_loop/14743_counting_coprime_pairs/14743.c) | Count coprime pairs | [🔗](https://acm.cs.nthu.edu.tw/problem/14743/) |
| [14780](Ch05_loop/14780_uniform_invoice_prize/14780.c) | Uniform invoice prize calculation | [🔗](https://acm.cs.nthu.edu.tw/problem/14780/) |

### Ch06 — 陣列

| 題號 | 題目 | 題目連結 |
|------|------|----------|
| [14702](Ch06_array/14702_print_values_in_sequence/14702.c) | Print odd/even indexed values | [🔗](https://acm.cs.nthu.edu.tw/problem/14702/) |
| [14703](Ch06_array/14703_average_score/14703.c) | Average score per student and course | [🔗](https://acm.cs.nthu.edu.tw/problem/14703/) |
| [14711](Ch06_array/14711_3d_bingo_cube/14711.c) | 3D Bingo Cube | [🔗](https://acm.cs.nthu.edu.tw/problem/14711/) |
| [14713](Ch06_array/14713_third_closest_point/14713.c) | Third closest point to origin (3D) | [🔗](https://acm.cs.nthu.edu.tw/problem/14713/) |
| [14714](Ch06_array/14714_tic_tac_toe/14714.c) | Tic-Tac-Toe | [🔗](https://acm.cs.nthu.edu.tw/problem/14714/) |
| [14716](Ch06_array/14716_odd_even_separation/14716.c) | Odd and even separation | [🔗](https://acm.cs.nthu.edu.tw/problem/14716/) |
| [14739](Ch06_array/14739_mirror_room/14739.c) | Mirror Room with −45° mirrors | [🔗](https://acm.cs.nthu.edu.tw/problem/14739/) |
| [14740](Ch06_array/14740_spiral_traversal/14740.c) | Spiral traversal of matrix | [🔗](https://acm.cs.nthu.edu.tw/problem/14740/) |
| [14757](Ch06_array/14757_matrix_maximum/14757.c) | Matrix maximum (4×4) | [🔗](https://acm.cs.nthu.edu.tw/problem/14757/) |
| [14777](Ch06_array/14777_graphic_rotation/14777.c) | Graphic rotation | [🔗](https://acm.cs.nthu.edu.tw/problem/14777/) |
| [14781](Ch06_array/14781_word_frequency/14781.c) | Word frequency count | [🔗](https://acm.cs.nthu.edu.tw/problem/14781/) |
| [14791](Ch06_array/14791_combination_sum/14791.c) | Combination sum | [🔗](https://acm.cs.nthu.edu.tw/problem/14791/) |

### Ch07 — 浮點數

| 題號 | 題目 | 題目連結 |
|------|------|----------|
| [14712](Ch07_float/14712_cosine_taylor_series/14712.c) | Cosine via Taylor series | [🔗](https://acm.cs.nthu.edu.tw/problem/14712/) |
| [14742](Ch07_float/14742_distance_two_points/14742.c) | Distance between two points (polar) | [🔗](https://acm.cs.nthu.edu.tw/problem/14742/) |
| [14744](Ch07_float/14744_quadratic_roots/14744.c) | Roots of a quadratic equation | [🔗](https://acm.cs.nthu.edu.tw/problem/14744/) |

### Ch08 — 函式

| 題號 | 題目 | 題目連結 |
|------|------|----------|
| [14708](Ch08_function/14708_longest_double_palindrome/14708.c) | Longest double palindrome | [🔗](https://acm.cs.nthu.edu.tw/problem/14708/) |
| [14794](Ch08_function/14794_evaluate_function_maximum/14794.c) | Evaluate function and find maximum | [🔗](https://acm.cs.nthu.edu.tw/problem/14794/) |

### Ch09 — 指標

| 題號 | 題目 | 題目連結 |
|------|------|----------|
| [14755](Ch09_pointer/14755_max_pointer_array/14755.c) | Maximum value via pointer array | [🔗](https://acm.cs.nthu.edu.tw/problem/14755/) |
| [14756](Ch09_pointer/14756_upper_triangular_solver/14756.c) | Upper-triangular linear system solver | [🔗](https://acm.cs.nthu.edu.tw/problem/14756/) |
| [14758](Ch09_pointer/14758_pointer_add_function/14758.c) | Pointer add function | [🔗](https://acm.cs.nthu.edu.tw/problem/14758/) |

### Ch11 — 字串

| 題號 | 題目 | 題目連結 |
|------|------|----------|
| [14778](Ch11_string/14778_plural_forms/14778.c) | English plural forms | [🔗](https://acm.cs.nthu.edu.tw/problem/14778/) |
| [14779](Ch11_string/14779_word_similarity/14779.c) | Word similarity judgment | [🔗](https://acm.cs.nthu.edu.tw/problem/14779/) |
| [14802](Ch11_string/14802_add_large_integers/14802.c) | Add two large integers (string) | [🔗](https://acm.cs.nthu.edu.tw/problem/14802/) |
| [14820](Ch11_string/14820_database_server/14820.c) | Database server (SQL-like queries) | [🔗](https://acm.cs.nthu.edu.tw/problem/14820/) |
| [14875](Ch11_string/14875_date_format_converter/14875.c) | Date format converter | [🔗](https://acm.cs.nthu.edu.tw/problem/14875/) |
| [14877](Ch11_string/14877_word_sorting/14877.c) | Word sorting | [🔗](https://acm.cs.nthu.edu.tw/problem/14877/) |

### Ch14 — 結構

| 題號 | 題目 | 題目連結 |
|------|------|----------|
| [14803](Ch14_structure/14803_subnet_determination/14803.c) | Subnet determination count | [🔗](https://acm.cs.nthu.edu.tw/problem/14803/) |
| [14804](Ch14_structure/14804_bookshelf_management/14804.c) | Simulated bookshelf management | [🔗](https://acm.cs.nthu.edu.tw/problem/14804/) |
| [14819](Ch14_structure/14819_average_grade/14819.c) | Average grade (struct) | [🔗](https://acm.cs.nthu.edu.tw/problem/14819/) |
| [14822](Ch14_structure/14822_tic_tac_toe_winner/14822.c) | Tic-Tac-Toe winner (struct version) | [🔗](https://acm.cs.nthu.edu.tw/problem/14822/) |

### Ch15 — 遞迴

| 題號 | 題目 | 題目連結 |
|------|------|----------|
| [14824](Ch15_recursion/14824_map_coloring/14824.c) | Map coloring (backtracking) | [🔗](https://acm.cs.nthu.edu.tw/problem/14824/) |
| [14825](Ch15_recursion/14825_longest_common_subsequence/14825.c) | Longest common subsequence | [🔗](https://acm.cs.nthu.edu.tw/problem/14825/) |
| [14829](Ch15_recursion/14829_max_profit_cutting/14829.c) | Maximum profit from cutting a rectangle | [🔗](https://acm.cs.nthu.edu.tw/problem/14829/) |
| [14830](Ch15_recursion/14830_mahjong_winning_tiles/14830.c) | Mahjong winning tiles | [🔗](https://acm.cs.nthu.edu.tw/problem/14830/) |
| [14835](Ch15_recursion/14835_friendship/14835.c) | Friendship (binary file) | [🔗](https://acm.cs.nthu.edu.tw/problem/14835/) |
| [14836](Ch15_recursion/14836_reverse_linked_list/14836.c) | Reverse output of linked list | [🔗](https://acm.cs.nthu.edu.tw/problem/14836/) |
| [14850](Ch15_recursion/14850_skyline/14850.c) | The Skyline Problem | [🔗](https://acm.cs.nthu.edu.tw/problem/14850/) |
| [14866](Ch15_recursion/14866_josephus/14866.c) | Josephus problem | [🔗](https://acm.cs.nthu.edu.tw/problem/14866/) |
| [14878](Ch15_recursion/14878_l_tromino_tiling/14878.c) | L-tromino tiling | [🔗](https://acm.cs.nthu.edu.tw/problem/14878/) |

### Ch16 — 檔案處理

| 題號 | 題目 | 題目連結 |
|------|------|----------|
| [14834](Ch16_file/14834_binary_file_comparison/14834.c) | Binary file comparison | [🔗](https://acm.cs.nthu.edu.tw/problem/14834/) |
| [14843](Ch16_file/14843_file_comparison/14843.c) | Text file comparison | [🔗](https://acm.cs.nthu.edu.tw/problem/14843/) |
| [14844](Ch16_file/14844_file_splitting/14844.c) | File splitting | [🔗](https://acm.cs.nthu.edu.tw/problem/14844/) |

### Ch17 — 資料結構

| 題號 | 題目 | 題目連結 |
|------|------|----------|
| [14823](Ch17_data_structure/14823_same_supervisor/14823.c) | Same direct supervisor | [🔗](https://acm.cs.nthu.edu.tw/problem/14823/) |
| [14846](Ch17_data_structure/14846_event_triggering/14846.c) | Event triggering logic inference | [🔗](https://acm.cs.nthu.edu.tw/problem/14846/) |
| [14847](Ch17_data_structure/14847_bst_subtree_size/14847.c) | BST subtree size computation | [🔗](https://acm.cs.nthu.edu.tw/problem/14847/) |
| [14849](Ch17_data_structure/14849_bookshelf_linked_list/14849.c) | Bookshelf management (linked list) | [🔗](https://acm.cs.nthu.edu.tw/problem/14849/) |
| [14859](Ch17_data_structure/14859_kth_smallest_bst/14859.c) | k-th smallest in BST | [🔗](https://acm.cs.nthu.edu.tw/problem/14859/) |
| [14864](Ch17_data_structure/14864_map_color/14864.c) | Map color (graph coloring) | [🔗](https://acm.cs.nthu.edu.tw/problem/14864/) |
| [14865](Ch17_data_structure/14865_employee_network/14865.c) | Employee network | [🔗](https://acm.cs.nthu.edu.tw/problem/14865/) |
| [14871](Ch17_data_structure/14871_queue_operations/14871.c) | Queue operations | [🔗](https://acm.cs.nthu.edu.tw/problem/14871/) |
| [14874](Ch17_data_structure/14874_build_binary_tree/14874.c) | Build binary tree | [🔗](https://acm.cs.nthu.edu.tw/problem/14874/) |

### Ch18 — 物件

| 題號 | 題目 | 題目連結 |
|------|------|----------|
| [14858](Ch18_object/14858_expression_calculator/14858.c) | Expression calculator | [🔗](https://acm.cs.nthu.edu.tw/problem/14858/) |

---

by EEccliTA, NTHU
