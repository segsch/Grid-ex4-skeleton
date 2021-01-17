#include "gtest/gtest.h"
#include "Grid.h"
#include "CoordinatesMath.h"
#include <cassert>

TEST(GISEx4, DocTest) {
    struct A {
        virtual ~A() {}
        virtual void foo() const = 0;
    };
    struct B : A { void foo() const override {} };
    struct C : A { void foo() const override {} };
    struct D : C { void foodie() const {} };

    Coordinates coord{Longitude{20}, Latitude{30}};
    Grid<A, 1917> grid;
    const auto cell_ptr = grid.getCellAt(coord); 
    auto viewD = cell_ptr->getEntitiesView<D>(); // O(1), always, even for size == N
    EXPECT_EQ(viewD.size(), 0ul); // assume passed successfully

    // adding a D object to the Grid, such that it should be added to the cell at coord  
    D dees[4];
    const auto cell_ptr2 = grid.add(coord, dees[0]);
    EXPECT_EQ(viewD.size(), 1ul); // the new object shall be in the view
    EXPECT_EQ(cell_ptr2, cell_ptr);

    // adding 3 D objects to the Grid, such that it should be added to the cell at coord  
    for(int i=1; i<4; ++i) {
        EXPECT_EQ(grid.add(coord, dees[i]), cell_ptr);
    }
    
    EXPECT_EQ(viewD.size(), 4ul); // the new objects shall be in the view

    int i=0;
    for(D* pd: viewD) { // correct type
        pd->foodie();
        EXPECT_EQ(pd, &dees[i]);
        ++i;
    }
}
