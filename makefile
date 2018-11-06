all:
	emcc -O2 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s WASM=1 \
		-s ENVIRONMENT=web -s MODULARIZE=1 -s ALLOW_MEMORY_GROWTH=1 \
		-s NO_EXIT_RUNTIME=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall"]'\
		-I/usr/local/include -L/usr/local/lib \
		-I/usr/local/Cellar/cbc/2.9.9_1/include/cbc/coin \
		-I/usr/local/Cellar/cgl/0.59.10/include/cgl/coin \
		-I/usr/local/Cellar/clp/1.16.11/include/clp/coin \
		-I/usr/local/Cellar/osi/0.107.9/include/osi/coin \
		-I/usr/local/Cellar/coinutils/2.10.14/include/coinutils/coin \
		-L/usr/local/Cellar/cbc/2.9.9_1/lib \
		-L/usr/local/Cellar/cgl/0.59.10/lib \
		-L/usr/local/Cellar/clp/1.16.11/lib \
		-L/usr/local/Cellar/osi/0.107.9/lib \
		-L/usr/local/Cellar/coinutils/2.10.14/lib \
		-lCbcSolver -lCbc -lCgl -lOsiClp -lClpSolver -lClp -lOsi -lCoinUtils \
		-o out/knapsack.js ./knapsack.cpp
