P_count=0
F_count=0
S_Grade=0

for((i=1;i<10;i++));do
	read -p "Please input integar:" a
	if[$a -ge 60 ];
		P_count=((P_count++))
	else
		F_count=((F_count++))
	fi
		S_Grade+=$a
done

echo "PassedNumber:$P_count"
echo "FailedNumber:$F_count"
echo "Average:$S_Grade/10"



