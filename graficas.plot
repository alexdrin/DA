set xlabel 'Número de vértices (V)'
set ylabel 'Tiempo (segundos)'
set title 'Kruskal: Preordenación vs Montículos (Peor Caso)'
set grid
set key left top
set style data linespoints

# Representación en ventana flotante
set terminal qt size 1024, 768 persist

plot 'tiempos.tmp' using 1:2 skip 1 title 'Preordenación' linecolor rgb 'blue', \
     'tiempos.tmp' using 1:3 skip 1 title 'Montículos' linecolor rgb 'red'