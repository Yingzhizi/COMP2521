if（mark < 50)      grade = 'F';
else if（mark < 65) grade = 'P';
else if（mark < 75) grade = 'C';
else if（mark < 85) grade = 'D';
else                grade = 'H';

#simpled c function
if (mark >= 50) goto case2;
grade = 'F';
goto end_if;

case2:
if(mark >= 65) goto case3;
grade = 'P';
goto end_if;

case3:
if(mark >= 75) goto case4;
grade = 'C';
goto end_if;

case4:
if(mark >= 85) goto case5;
grade = 'D';
goto end_if;

case5:
grade = 'H';
goto
