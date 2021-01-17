#include "gtest/gtest.h"
#include "Grid.h"
#include "CoordinatesMath.h"
#include <cassert>

TEST(GISEx4, DocTest) {
    Coordinates coord{Longitude{20}, Latitude{30}};
    // const Grid::Cell* cell = grid.getCellAt(coord); 
    // auto viewD = cell->getEntitiesView<D>(); // O(1), always, even for size == N
    // assert ( viewD.size() == 0 ); // assume passed successfully
    // // adding a D object to the Grid, such that it should be added to the cell at coord
    // assert ( viewD.size() == 1 ); // the new object shall be in the view
    // // adding three additional D objects via the Grid, that should be added to this cell
    // assert ( viewD.size() == 4 ); // the new objects shall be added at the end
    // for(D* pd: viewD) { // correct type
    // pd->call_a_function_appearing_only_in_class_D_without_casting();
    // }
}
