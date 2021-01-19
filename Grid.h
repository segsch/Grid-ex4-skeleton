#pragma once

#include "GISNamedTypes.h"
#include <vector>

// Two concepts required by the below functions:

template<class Me, class Other> concept derived_or_same =
    std::same_as<Me, Other> || std::derived_from<Me, Other>;

template<class Me, class Other> concept concrete_derived_or_same =
	!std::is_abstract_v<Me> && derived_or_same<Me, Other>;

// class Grid
template<typename Entity, std::size_t num_rows> requires (num_rows > 0)
class Grid { 

    // private inner class Cell
    class Cell { 
    public:
        // Cell’s Constructors and Assignment:
        // There are no constructors that are required by the API. You should decide whether to implement, block or rely on the default for copy and move constructors, as well as for the assignment operators.

        // Cell’s Destructor:
        // You should decide whether there is a need to implement a user defined destructor.

        // (Cell::A1) Getting Entities from a Cell:
        // returns all entities in that cell, which return true for the PredicateFunc.
        template<typename PredicateFunc>
        std::vector<Entity*> getEntities(PredicateFunc&&) const {
            // TODO: implement 
            return std::vector<Entity*>{};
        }

        // (Cell::B1) 
        // Getting specific type of Entities from a Cell:
        // returns all entities of type ActualT which return true for the PredicateFunc.
        template<typename ActualT, typename PredicateFunc> 
        requires concrete_derived_or_same<ActualT, Entity>
        std::vector<ActualT*> getEntities(PredicateFunc&&) const {
            // TODO: implement
            return std::vector<ActualT*>{};
        }

        // (Cell::B2) 
        // same as (Cell::B1) above but with a limit on the number of returned entities (up to limit entities).
        template<typename ActualT, typename PredicateFunc> requires concrete_derived_or_same<ActualT, Entity>
        std::vector<ActualT*> getEntities(PredicateFunc&&, std::size_t limit) const {
            // TODO: implement
            (void) limit; 
            return std::vector<ActualT*>{};
        }

        // (Cell::B3) 
        // returns a range of all entities of type ActualT.
        // Complexity of this function is required to be O(1)
        // This function returns a view that is updated “behind the scene” automatically in case additional objects of type ActualT are added to this Cell via the Grid. Order of entities in the view shall be the same as the order of their insertion to the grid.
        // Iterating over the returned view generates pointers with the correct type, i.e. ActualT*.
        template<typename ActualT> requires concrete_derived_or_same<ActualT, Entity>
        std::ranges::sized_range auto getEntitiesView() const {
            // TODO: implement  
            static std::vector<ActualT*> stub_vec{};
            return std::ranges::ref_view(stub_vec);
        }
   
        // Additional auxiliary functions:

        // (Cell::C1) 
        std::size_t numEntities() const noexcept {
            // TODO: implement  
            return 0;
        }

        // (Cell::C2) 
        // NOTE: complexity required to be O(1)
        template<typename ActualT> requires concrete_derived_or_same<ActualT, Entity>
        std::size_t numEntities() const noexcept { 
            // TODO: implement  
            return 0;
        }

        // Iterators begin and end:
        // The Cell would have begin and end iterators for iterating over all pointers to Entity. Retrieved pointers are non-const, i.e. the user can call non-const methods on the retrieved entities. There is no defined order for the iteration. Iteration itself shall not create any copies.
        auto begin() const noexcept { 
            // TODO: implement
            static std::vector<Entity*> stub_vec1;
            return stub_vec1.begin(); 
        }

        auto end() const noexcept { 
            // TODO: implement
            static std::vector<Entity*> stub_vec2;
            return stub_vec2.end(); 
        }
    };

public:
    // Grid’s Constructors and Assignment:
    // There are no constructors that are required by the API. You should decide whether to implement, block or rely on the default for copy and move constructors, as well as for the assignment operators.

    // Grid’s Destructor:
    // You should decide whether there is a need to implement a user defined destructor.

    // Adding Entities to the Grid:

    // (Grid::A1) 
    template<typename ActualT> requires derived_or_same<ActualT, Entity>
    const Cell* add(Coordinates c, ActualT& e) {
        // TODO: implement
        (void) c; 
        (void) e; 
        static Cell dummy_cell1{};
        return &dummy_cell1;
    }

    // Getting Cells from the Grid:

    // (Grid::B1) 
    const Cell* getCellAt(Coordinates c) const {
        // TODO: implement 
        (void) c;
        static Cell dummy_cell2{};
        return &dummy_cell2;
    }

    // (Grid::B2) (BONUS: you may choose not to implemnt this function)
    std::vector<const Cell*> getCellsAt(Coordinates center, Meters radius) const {
        (void) center; 
        (void) radius; 
        return std::vector<const Cell*>{};
    }

    // additional auxiliary functions:

    // (Grid::C1) 
    std::size_t numRows() const noexcept {
        return num_rows;
    } 
    
    // (Grid::C2) 
    std::size_t numCols(Coordinates c) const noexcept {
        // TODO: implement  
        return 13;
    }

    // (Grid::C3) 
    std::size_t numCells() const noexcept {
        // TODO: implement  
        return 432; 
    }

    // iterators begin and end:
    // The Grid would have a const version of begin and end iterators for iterating over all Cells. There is no defined order for the iteration. The iteration itself shall not create any copies.    
    
    // Set this to true if you are implementing a sparse grid.
    static constexpr bool is_sparse = false;  
 
    // Following would iterate over:
    // 1. Only non empty Cells, if is_sparse==true 
    // 2. All Cells, if is_sparse==false

    auto begin() const noexcept { 
        // TODO: implement
        static std::vector<Cell&> stub_vec1;
        return stub_vec1.begin(); 
    }

    auto end() const noexcept { 
        // TODO: implement
        static std::vector<Cell&> stub_vec2;
        return stub_vec2.end(); 
    }
};
