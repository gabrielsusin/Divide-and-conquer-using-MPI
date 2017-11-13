
echo -e "Qsort 100000"
./seqQsortDC -size 100000
mpirun -np 1 qsortDC -delta 100000 -size 100000
mpirun -np 3 qsortDC -delta 50000 -size 100000
mpirun -np 7 qsortDC -delta 25000 -size 100000
mpirun -np 15 qsortDC -delta 12500 -size 100000
mpirun -np 31 qsortDC -delta 6250 -size 100000

echo -e "Qsort_modified 100000"
mpirun -np 1 qsortDC_modified -delta 100000 -size 100000
mpirun -np 3 qsortDC_modified -delta 50000 -size 100000
mpirun -np 7 qsortDC_modified -delta 25000 -size 100000
mpirun -np 15 qsortDC_modified -delta 12500 -size 100000
mpirun -np 31 qsortDC_modified -delta 6250 -size 100000

echo -e "Qsort 1000000"
./seqQsortDC -size 1000000
mpirun -np 1 qsortDC -delta 1000000 -size 1000000
mpirun -np 3 qsortDC -delta 500000 -size 1000000
mpirun -np 7 qsortDC -delta 250000 -size 1000000
mpirun -np 15 qsortDC -delta 125000 -size 1000000
mpirun -np 31 qsortDC -delta 62500 -size 1000000

echo -e "Qsort_modified 1000000"
mpirun -np 1 qsortDC_modified -delta 1000000 -size 1000000
mpirun -np 3 qsortDC_modified -delta 500000 -size 1000000
mpirun -np 7 qsortDC_modified -delta 250000 -size 1000000
mpirun -np 15 qsortDC_modified -delta 125000 -size 1000000
mpirun -np 31 qsortDC_modified -delta 62500 -size 1000000

echo -e "Bsort 100000"
./seqBubbleDC -size 100000
mpirun -np 1 BubbleDC -delta 100000 -size 100000
mpirun -np 3 BubbleDC -delta 50000 -size 100000
mpirun -np 7 BubbleDC -delta 25000 -size 100000
mpirun -np 15 BubbleDC -delta 12500 -size 100000
mpirun -np 31 BubbleDC -delta 6250 -size 100000

echo -e "Bsort_modified 100000"
mpirun -np 1 BubbleDC_modified -delta 100000 -size 100000
mpirun -np 3 BubbleDC_modified -delta 50000 -size 100000
mpirun -np 7 BubbleDC_modified -delta 25000 -size 100000
mpirun -np 15 BubbleDC_modified -delta 12500 -size 100000
mpirun -np 31 BubbleDC_modified -delta 6250 -size 100000

echo -e "Bsort 1000000"
./seqQsortDC -size 1000000
mpirun -np 1 BubbleDC -delta 1000000 -size 1000000
mpirun -np 3 BubbleDC -delta 500000 -size 1000000
mpirun -np 7 BubbleDC -delta 250000 -size 1000000
mpirun -np 15 BubbleDC -delta 125000 -size 1000000
mpirun -np 31 BubbleDC -delta 62500 -size 1000000

echo -e "Bsort_modified 1000000"
mpirun -np 1 BubbleDC_modified -delta 1000000 -size 1000000
mpirun -np 3 BubbleDC_modified -delta 500000 -size 1000000
mpirun -np 7 BubbleDC_modified -delta 250000 -size 1000000
mpirun -np 15 BubbleDC_modified -delta 125000 -size 1000000
mpirun -np 31 BubbleDC_modified -delta 62500 -size 1000000
