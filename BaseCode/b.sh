P_count=0
F_count=0
S_Grade=0

for ((i=1;i<=10;i++));do
        read -p "Please input the '$i'th Grade:" Score
        if [ "$Score" -ge 60 ]; then
                P_count=$((P_count+1))
        else
                F_count=$((F_count+1))
        fi

        S_Grade=$((S_Grade+Score))
done
#average
average_score=$((S_Grade/10))

echo "Passed Number is $P_count"
echo "Failed Number is $F_count"
echo "Average Score is $average_score"
