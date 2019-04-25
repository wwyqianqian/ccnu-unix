#! /bin/bash
echo "请输入学生人数:"
read stu_num
count="0"
course1="0"
course2="0"
course3="0"

while [ $count -lt $stu_num ]
	do
		coursesum=0
		echo "输入学生姓名:"
		read stu_name
		echo "输入课程1分数:"
			read courseone
			coursesum=`expr $coursesum + $courseone`
			course1=`expr $course1 + $courseone`
		echo "输入课程2分数:"
			read coursetwo
			coursesum=`expr $coursesum + $coursetwo`
			course2=`expr $course2 + $coursetwo`
		echo "输入课程3分数:"
			read coursethree
			coursesum=`expr $coursesum + $coursethree`
			course3=`expr $course3 + $coursethree`
		echo $stu_name "总分为" $coursesum
		count=`expr $count + 1`
done

course1_ave=`expr $course1 / $stu_num`
course2_ave=`expr $course2 / $stu_num`
course3_ave=`expr $course3 / $stu_num`

echo "课程1平均分为" $course1_ave "课程2平均分为" $course2_ave "课程3平均分为" $course3_ave 
