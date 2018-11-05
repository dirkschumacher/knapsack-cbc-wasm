
#include <CbcSolver.hpp>
#include <emscripten/emscripten.h>

#ifdef __cplusplus
extern "C" {
#endif

double* EMSCRIPTEN_KEEPALIVE knapsack(int nCols,
                                      double* obj,
                                      double* weights,
                                      double capacity) {

  std::vector<int> rowIndices(nCols);
  std::vector<int> colIndices(nCols);
  std::vector<double> lbCol(nCols);
  std::vector<double> ubCol(nCols);
  for (int i = 0; i < nCols; i++) {
    rowIndices[i] = 0;
    colIndices[i] = i;
    lbCol[i] = 0;
    ubCol[i] = 1;
  }
  double lbRow0[] = { 0 };
  double ubRow1[] = { 1 };

  CoinPackedMatrix matrix(true,
                          rowIndices.data(),
                          colIndices.data(),
                          weights,
                          nCols);

  OsiClpSolverInterface solver;
  solver.loadProblem(matrix,
                     lbCol.data(),
                     ubCol.data(),
                     obj,
                     lbRow0,
                     ubRow1);

  // // set integer variables
  for(int i = 0; i < nCols; i++) {
    solver.setInteger(i);
  }

  CbcModel model(solver);
  CbcMain0(model);

  const char * argList[0]; // no args for now
  CbcMain1(0, argList, model);

  std::vector<double> solution(nCols);

  const double *solverSolution = model.solver()->getColSolution();
  for(int i = 0; i < nCols; i++) {
    solution[i] = solverSolution[i];
  }

  return solution.data();
}

#ifdef __cplusplus
}
#endif

