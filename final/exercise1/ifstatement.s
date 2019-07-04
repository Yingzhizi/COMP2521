#if（mark < 50)      grade = 'F';
#else if（mark < 65) grade = 'P';
#else if（mark < 75) grade = 'C';
#else if（mark < 85) grade = 'D';
#else                grade = 'H';

if_start:
    lw $t0, mark            #t0 = mark
    li $t1, 50
    blt $t0, $t1, f_grade   #branch to f_grade if t0 < t1

    li $t1, 65
    blt $t0, $t1, p_grade   #branch to p_grade if t0 < t1

    li $t1, 75
    blt $t0, $t1, c_grade

    li $t1, 85
    blt $t0, $t1, d_grade

    lb $t1, 'H'
    sb $t1, grade
    j end_if

f_grade:
    lb $t1, 'F'
    sb $t1, grade
    j       end_if

p_grade:
    lb $t1, 'P'
    sb $t1, grade
    j       end_if
p_grade:
    lb $t1, 'C'
    sb $t1, grade
    j       end_if

p_grade:
    lb $t1, 'D'
    sb $t1, grade
    j       end_if
