
echo -e "Qsort 100000"
ladrun -np 1 qsortDC -delta 100000 -size 100000
ladrun -np 3 qsortDC -delta 50000 -size 100000
ladrun -np 7 qsortDC -delta 25000 -size 100000
ladrun -np 15 qsortDC -delta 12500 -size 100000
ladrun -np 31 qsortDC -delta 6250 -size 100000
ladrun -np 63 qsortDC -delta 3125 -size 100000

echo -e "Qsort_modified 100000"
ladrun -np 1 qsortDC_modified -delta 100000 -size 100000
ladrun -np 3 qsortDC_modified -delta 50000 -size 100000
ladrun -np 7 qsortDC_modified -delta 25000 -size 100000
ladrun -np 15 qsortDC_modified -delta 12500 -size 100000
ladrun -np 31 qsortDC_modified -delta 6250 -size 100000

echo -e "Qsort 1000000"
ladrun -np 1 qsortDC -delta 1000000 -size 1000000
ladrun -np 3 qsortDC -delta 500000 -size 1000000
ladrun -np 7 qsortDC -delta 250000 -size 1000000
ladrun -np 15 qsortDC -delta 125000 -size 1000000
ladrun -np 31 qsortDC -delta 62500 -size 1000000
ladrun -np 63 qsortDC -delta 31250 -size 1000000

echo -e "Qsort_modified 1000000"
ladrun -np 1 qsortDC_modified -delta 1000000 -size 1000000
ladrun -np 3 qsortDC_modified -delta 500000 -size 1000000
ladrun -np 7 qsortDC_modified -delta 250000 -size 1000000
ladrun -np 15 qsortDC_modified -delta 125000 -size 1000000
ladrun -np 31 qsortDC_modified -delta 62500 -size 1000000

echo -e "Bsort 100000"
ladrun -np 1 bubbleDC -delta 100000 -size 100000
ladrun -np 3 bubbleDC -delta 50000 -size 100000
ladrun -np 7 bubbleDC -delta 25000 -size 100000
ladrun -np 15 bubbleDC -delta 12500 -size 100000
ladrun -np 31 bubbleDC -delta 6250 -size 100000
ladrun -np 63 bubbleDC -delta 3125 -size 100000

echo -e "Bsort_modified 100000"
ladrun -np 1 bubbleDC_modified -delta 100000 -size 100000
ladrun -np 3 bubbleDC_modified -delta 50000 -size 100000
ladrun -np 7 bubbleDC_modified -delta 25000 -size 100000
ladrun -np 15 bubbleDC_modified -delta 12500 -size 100000
ladrun -np 31 bubbleDC_modified -delta 6250 -size 100000

echo -e "Bsort 1000000"
ladrun -np 1 bubbleDC -delta 1000000 -size 1000000
ladrun -np 3 bubbleDC -delta 500000 -size 1000000
ladrun -np 7 bubbleDC -delta 250000 -size 1000000
ladrun -np 15 bubbleDC -delta 125000 -size 1000000
ladrun -np 31 bubbleDC -delta 62500 -size 1000000
ladrun -np 63 bubbleDC -delta 31250 -size 1000000

echo -e "Bsort_modified 1000000"
ladrun -np 1 bubbleDC_modified -delta 1000000 -size 1000000
ladrun -np 3 bubbleDC_modified -delta 500000 -size 1000000
ladrun -np 7 bubbleDC_modified -delta 250000 -size 1000000
ladrun -np 15 bubbleDC_modified -delta 125000 -size 1000000
ladrun -np 31 bubbleDC_modified -delta 62500 -size 1000000
