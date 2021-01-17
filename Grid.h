#pragma once
#include "GISNamedTypes.h"

// Two concepts required by the below functions:

template<class Me, class Other> concept derived_or_same =
        std::same_as<Me, Other> || std::derived_from<Me, Other>;

template<class Me, class Other> concept concrete_derived_or_same =
	!std::is_abstract_v<Me> && derived_or_same<Me, Other>;

// Grid’s public API

template<typename Entity, std::size_t num_rows> requires (num_rows > 0)
class Grid { 
public:
    class Cell { 
        // Cell’s Constructors and Assignment:
        // There are no constructors that are required by the API. You should decide whether to implement, block or rely on the default for copy and move constructors, as well as for the assignment operators.

        // Cell’s Destructor:
        // You should decide whether there is a need to implement a user defined destructor.

        // [1] Getting Entities from a Cell:
        // returns all entities in that cell, which return true for the PredicateFunc.
        template<typename PredicateFunc>
            std::vector<Entity*> getEntities(PredicateFunc&&) const;

        // [2] 
        // same as (1) above but for a given circle (that may be in the cell or not, partially or in a whole).
        template<typename PredicateFunc>
            std::vector<Entity*> getEntities(Coordinates center, Meters radius, PredicateFunc&&) const;

        // [3] 
        // same as (1) above but with a limit on the number of returned entities (up to limit entities).
        template<typename PredicateFunc>
            std::vector<Entity*> getEntities(PredicateFunc&&, std::size_t limit) const;

        // [4] 
        // same as (2) above but with a limit on the number of returned entities (up to limit entities).
        template<typename PredicateFunc>
            std::vector<Entity*> getEntities(Coordinates center, Meters radius, PredicateFunc&&, std::size_t limit) const;


        // [1] Getting specific type of Entities from a Cell:
        // returns all entities of type ActualT which return true for the PredicateFunc.
        template<typename ActualT, typename PredicateFunc> 
        requires concrete_derived_or_same<ActualT, Entity>
            std::vector<ActualT*> getEntities(PredicateFunc&&) const;

        // [2] 
        // same as (1) above, with a limiting circle.
        template<typename ActualT, typename PredicateFunc>
        requires concrete_derived_or_same<ActualT, Entity>
            std::vector<ActualT*> getEntities(Coordinates center, Meters radius, PredicateFunc&&) const;

        // [3] 
        // same as (1) above but with a limit on the number of returned entities (up to limit entities).
        template<typename ActualT, typename PredicateFunc>
        requires concrete_derived_or_same<ActualT, Entity>
            std::vector<ActualT*> getEntities(PredicateFunc&&, std::size_t limit) const;

        // [4] same as (2) above but with a limit on the number of returned entities (up to limit entities).
        template<typename ActualT, typename PredicateFunc>
        requires concrete_derived_or_same<ActualT, Entity>
        std::vector<ActualT*> getEntities(Coordinates center, Meters radius,
            PredicateFunc&&, std::size_t limit) const;

        // [5] 
        // returns a range of all entities of type ActualT.
        template<typename ActualT>
        requires concrete_derived_or_same<ActualT, Entity>
            std::ranges::sized_range auto getEntitiesView() const;

        // NOTEs:
        // Complexity of this function is required to be O(1)
        // This function returns a view that is updated “behind the scene” automatically in case additional objects of type ActualT are added to this Cell via the Grid. Order of entities in the view shall be the same as the order of their insertion to the grid.
        // Iterating over the returned view generates pointers with the correct type, i.e. ActualT*.
   
        // Iterators begin and end:
        // The Cell would have begin and end iterators for iterating over all pointers to Entity. Retrieved pointers are non-const, i.e. the user can call non-const methods on the retrieved entities. There is no defined order for the iteration. Iteration itself shall not create any copies.
    
        // Additional auxiliary functions:
        std::size_t numEntities() const noexcept;

        template<typename ActualT>
        requires concrete_derived_or_same<ActualT, Entity>
            std::size_t numEntities() const noexcept; // NOTE: complexity required to be O(1)
    };

    // Grid’s Constructors and Assignment:
    // There are no constructors that are required by the API. You should decide whether to implement, block or rely on the default for copy and move constructors, as well as for the assignment operators.

    // Grid’s Destructor:
    // You should decide whether there is a need to implement a user defined destructor.

    // Adding Entities to the Grid:

    template<typename ActualT> requires derived_or_same<ActualT, Entity>
        const Cell* add(Coordinates c, ActualT& e);

    template<typename ActualT> requires derived_or_same<ActualT, Entity>
        std::vector<const Cell*> add(Coordinates from, Coordinates to, ActualT& e);

    template<typename ActualT> requires derived_or_same<ActualT, Entity>
        std::vector<const Cell*> add(Coordinates center, Meters radius, ActualT& e);

    // Getting Cells from the Grid:
    const Cell* getCellAt(Coordinates c) const;

    std::vector<const Cell*> getCellsAt(Coordinates center, Meters radius) const;

    // [1] Getting Entities from the Grid:
    // returns all entities in and on the circle, which return true for the PredicateFunc.
    template<typename PredicateFunc>
        std::vector<Entity*> getEntities(Coordinates center, Meters radius, PredicateFunc&&) const;


    // [2] 
    // same as (1) above but with a limit on the number of returned entities (up to limit entities).
    template<typename PredicateFunc>
        std::vector<Entity*> getEntities(Coordinates center, Meters radius, PredicateFunc&&, std::size_t limit) const;


    // [1] Getting specific type of Entities from the Grid:
    // returns all entities of type ActualT in and on the circle, which return true for the PredicateFunc.
    template<typename ActualT, typename PredicateFunc> requires concrete_derived_or_same<ActualT, Entity>
        std::vector<ActualT*> getEntities(Coordinates center, Meters radius, PredicateFunc&&) const;

    // [2]
    // same as (1) above but with a limit on the number of returned entities (up to limit entities).
    template<typename ActualT, typename PredicateFunc> requires concrete_derived_or_same<ActualT, Entity>
    std::vector<ActualT*> getEntities(Coordinates center, Meters radius, PredicateFunc&&, std::size_t limit) const;

    // additional auxiliary functions:
    std::size_t numRows() const noexcept; 
    std::size_t numCols(Coordinates c) const noexcept; 
    std::size_t numCells() const noexcept; 

    // iterators begin and end:
    // The Grid would have a const version of begin and end iterators for iterating over all Cells. There is no defined order for the iteration. The iteration itself shall not create any copies.

    // Cell’s public API

    // Cell shall be a nested private* class inside class Grid.
    //*	C++ allows calling public methods on an object obtained legally, even if the class itself is defined in some private scope. 
};
