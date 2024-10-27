# HW2 of partitioning and floorplan

**course: Optimization and Machine Learning in VLSI Design Automation (PKU 24 Fall)**

**Lecturer: Yibo Lin**

**TA: Chunyuan Zhao, Jincheng Lou**


Use sequence pair to solve floor plan(Not optimal)

Input: The first line is the number of modules n, the second line is the positive sequence, the third line is the negative sequence, and the following n lines are the width and height of each module.

Output: The first line is width and height of the layout. The following n lines are the lower-left corner of each module.

test:
```
input:
8
1 7 4 5 2 6 3 8
8 4 7 2 5 3 6 1
1 2 4
2 1 3
3 3 3
4 3 5
5 3 2
6 5 3
7 1 2
8 2 4
```
```
output:
11 15
0 11
3 4
6 4
0 4
3 7
6 7
0 9
0 0
```

# Recommend Reading：

- paritioning:
  - https://cc.ee.ntu.edu.tw/~ywchang/Courses/EDA/lec5.pdf
  - https://limsk.ece.gatech.edu/book/slides/pdf/KL-partitioning.pdf
  - https://limsk.ece.gatech.edu/book/slides/pdf/FM-partitioning.pdf

- floorplan:
  - https://cc.ee.ntu.edu.tw/~ywchang/Courses/EDA/lec3.pdf
  - https://limsk.ece.gatech.edu/book/slides/pdf/sequence-pair.pdf
  - http://cc.ee.ntu.edu.tw/~ywchang/Courses/PD_Source/EDA_floorplanning.pdf
