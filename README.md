# EE2310 C 程式設計 參考解答

NTHU EE2310《由片語學習C程式設計（第二版）》課程的 C 語言參考解答，依照課本章節分類整理。

## 說明

- 所有程式碼以簡單的 **C 語言**撰寫（不使用 C++ 語法）
- 每個檔案包含詳細的**繁體中文註解**
- 每題說明參考課本章節，方便對應學習

## 編譯方式

```bash
gcc -std=c99 -o out NNNNN.c -lm
```

部分題目需要 `-lm` 連結數學函式庫（如 `sin`、`cos`、`sqrt`）。

---

## 章節索引

### Ch02 — 基本運算

| 題號 | 題目 |
|------|------|
| [14651](Ch02_basic/14651_rectangle_perimeter_area/14651.c) | Compute rectangle perimeter and area |
| [14653](Ch02_basic/14653_max_three_integers/14653.c) | Maximum of three integers |
| [14667](Ch02_basic/14667_rect_area_2d/14667.c) | Rectangle area (2D) |
| [14668](Ch02_basic/14668_cuboid_surface_volume/14668.c) | Cuboid surface area and volume |
| [14742](Ch02_basic/14742_distance_two_points/14742.c) | Distance between two points (polar) |
| [14744](Ch02_basic/14744_quadratic_roots/14744.c) | Roots of a quadratic equation |

### Ch03 — 條件判斷

| 題號 | 題目 |
|------|------|
| [14682](Ch03_branch/14682_line_through_origin/14682.c) | Check if line passes through origin |
| [14683](Ch03_branch/14683_animals_in_cage/14683.c) | Animals in a cage (chicken & rabbit) |
| [14684](Ch03_branch/14684_triangle_inequality/14684.c) | Triangle inequality |
| [14685](Ch03_branch/14685_sum_four_digit/14685.c) | Sum of digits of a four-digit number |
| [14686](Ch03_branch/14686_multiple_determination/14686.c) | Multiple determination |
| [14687](Ch03_branch/14687_sum_integers/14687.c) | Sum of integers |
| [14688](Ch03_branch/14688_triangle_categories/14688.c) | Triangle categories |
| [14760](Ch03_branch/14760_line_through_3_18/14760.c) | Check if line passes through (3,18) |

### Ch04 — 迴圈

| 題號 | 題目 |
|------|------|
| [14699](Ch04_loop/14699_calculation_of_days/14699.c) | Calculation of days from 1970-01-01 |
| [14700](Ch04_loop/14700_carry_system_conversion/14700.c) | Number base conversion (2/8/10) |
| [14702](Ch04_loop/14702_print_values_in_sequence/14702.c) | Print odd/even indexed values |
| [14703](Ch04_loop/14703_average_score/14703.c) | Average score per student and course |
| [14706](Ch04_loop/14706_digit_rotation/14706.c) | Digit rotation |
| [14712](Ch04_loop/14712_cosine_taylor_series/14712.c) | Cosine via Taylor series |
| [14715](Ch04_loop/14715_prime_factorization/14715.c) | Prime factorization |
| [14716](Ch04_loop/14716_odd_even_separation/14716.c) | Odd and even separation |
| [14743](Ch04_loop/14743_counting_coprime_pairs/14743.c) | Count coprime pairs |
| [14780](Ch04_loop/14780_uniform_invoice_prize/14780.c) | Uniform invoice prize calculation |
| [14819](Ch04_loop/14819_average_grade/14819.c) | Average grade (struct) |

### Ch05 — 函數

| 題號 | 題目 |
|------|------|
| [14708](Ch05_function/14708_longest_double_palindrome/14708.c) | Longest double palindrome |
| [14794](Ch05_function/14794_evaluate_function_maximum/14794.c) | Evaluate function and find maximum |

### Ch06 — 陣列

| 題號 | 題目 |
|------|------|
| [14711](Ch06_array/14711_3d_bingo_cube/14711.c) | 3D Bingo Cube |
| [14713](Ch06_array/14713_third_closest_point/14713.c) | Third closest point to origin (3D) |
| [14714](Ch06_array/14714_tic_tac_toe/14714.c) | Tic-Tac-Toe |
| [14739](Ch06_array/14739_mirror_room/14739.c) | Mirror Room with −45° mirrors |
| [14740](Ch06_array/14740_spiral_traversal/14740.c) | Spiral traversal of matrix |
| [14757](Ch06_array/14757_matrix_maximum/14757.c) | Matrix maximum (4×4) |
| [14777](Ch06_array/14777_graphic_rotation/14777.c) | Graphic rotation |
| [14781](Ch06_array/14781_word_frequency/14781.c) | Word frequency count |
| [14791](Ch06_array/14791_combination_sum/14791.c) | Combination sum |
| [14822](Ch06_array/14822_tic_tac_toe_winner/14822.c) | Tic-Tac-Toe winner (struct version) |

### Ch07 — 字串

| 題號 | 題目 |
|------|------|
| [14778](Ch07_string/14778_plural_forms/14778.c) | English plural forms |
| [14779](Ch07_string/14779_word_similarity/14779.c) | Word similarity judgment |
| [14802](Ch07_string/14802_add_large_integers/14802.c) | Add two large integers (string) |
| [14813](Ch07_string/14813_add_large_integers_quiz/14813.c) | Add two large integers (quiz) |
| [14820](Ch07_string/14820_database_server/14820.c) | Database server (SQL-like queries) |
| [14877](Ch07_string/14877_word_sorting/14877.c) | Word sorting |

### Ch08 — 指標

| 題號 | 題目 |
|------|------|
| [14755](Ch08_pointer/14755_max_pointer_array/14755.c) | Maximum value via pointer array |
| [14756](Ch08_pointer/14756_upper_triangular_solver/14756.c) | Upper-triangular linear system solver |
| [14758](Ch08_pointer/14758_pointer_add_function/14758.c) | Pointer add function |
| [14761](Ch08_pointer/14761_min_pointer_array/14761.c) | Minimum value via pointer array |

### Ch09 — 結構

| 題號 | 題目 |
|------|------|
| [14803](Ch09_structure/14803_subnet_determination/14803.c) | Subnet determination count |
| [14804](Ch09_structure/14804_bookshelf_management/14804.c) | Simulated bookshelf management |
| [14814](Ch09_structure/14814_count_ips_same_subnet/14814.c) | Count IPs in same subnet |

### Ch10 — 檔案

| 題號 | 題目 |
|------|------|
| [14834](Ch10_file/14834_binary_file_comparison/14834.c) | Binary file comparison |
| [14843](Ch10_file/14843_file_comparison/14843.c) | Text file comparison |
| [14844](Ch10_file/14844_file_splitting/14844.c) | File splitting |

### Ch11 — 遞迴

| 題號 | 題目 |
|------|------|
| [14824](Ch11_recursion/14824_map_coloring/14824.c) | Map coloring (backtracking) |
| [14825](Ch11_recursion/14825_longest_common_subsequence/14825.c) | Longest common subsequence |
| [14829](Ch11_recursion/14829_max_profit_cutting/14829.c) | Maximum profit from cutting a rectangle |
| [14830](Ch11_recursion/14830_mahjong_winning_tiles/14830.c) | Mahjong winning tiles |
| [14835](Ch11_recursion/14835_friendship/14835.c) | Friendship (binary file) |
| [14836](Ch11_recursion/14836_reverse_linked_list/14836.c) | Reverse output of linked list |
| [14850](Ch11_recursion/14850_skyline/14850.c) | The Skyline Problem |
| [14866](Ch11_recursion/14866_josephus/14866.c) | Josephus problem |
| [14878](Ch11_recursion/14878_l_tromino_tiling/14878.c) | L-tromino tiling |

### Ch12 — 資料結構

| 題號 | 題目 |
|------|------|
| [14823](Ch12_data_structure/14823_same_supervisor/14823.c) | Same direct supervisor |
| [14846](Ch12_data_structure/14846_event_triggering/14846.c) | Event triggering logic inference |
| [14847](Ch12_data_structure/14847_bst_subtree_size/14847.c) | BST subtree size computation |
| [14849](Ch12_data_structure/14849_bookshelf_linked_list/14849.c) | Bookshelf management (linked list) |
| [14858](Ch12_data_structure/14858_expression_calculator/14858.c) | Expression calculator |
| [14859](Ch12_data_structure/14859_kth_smallest_bst/14859.c) | k-th smallest in BST |
| [14863](Ch12_data_structure/14863_kth_biggest_bst/14863.c) | k-th biggest in BST |
| [14864](Ch12_data_structure/14864_map_color/14864.c) | Map color (graph coloring) |
| [14865](Ch12_data_structure/14865_employee_network/14865.c) | Employee network |
| [14871](Ch12_data_structure/14871_queue_operations/14871.c) | Queue operations |
| [14874](Ch12_data_structure/14874_build_binary_tree/14874.c) | Build binary tree |
| [14875](Ch12_data_structure/14875_date_format_converter/14875.c) | Date format converter |

---

by EEccliTA, NTHU
