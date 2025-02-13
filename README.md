# Containers

Implementation of the s21_containers.h. library.

My own library implements the basic standard C++ container classes: `list`, `map`, `queue`, `set`, `stack`, `vector`, `array` and `multiset`. Implementations provide a full set of standard methods and attributes for element handling, container capacity checking and iteration.

Each type of containers provide the user with the following methods:

- standard constructors (default constructor, copy constructor, move constructor, constructor with initialization list, see materials);

- methods for accessing container elements (e.g. accessing an element with the index i);

- methods for checking if a container is full (e.g. the number of elements in the container, check if the container is empty);

- methods for changing the container (removing and adding new elements, cleaning the container);

- methods for dealing with the container iterator.

Iterators provide access to container elements. The specific type of iterator will be different for each container. This is due to the different way of organising object sets in container classes, as well as the actual implementation of the container. Iterators are implemented to work in a similar way to a pointer to an array element in C. So this approach to iterators allows you to interact with any container in the same way. Containers provide iterators via the `begin()` and `end()` methods, which point to the first and next after last elements of the container respectively.

Iterator `iter` has the following operations:

- `*iter`: gets the element pointed to by the iterator;

- `++iter`: moves the iterator forward to the next element;

- `--iter`: moves the iterator backwards to the previous element;

- `iter1 == iter2`: two iterators are equal if they point to the same element;

- `iter1 != iter2`: two iterators are not equal if they point to different elements.

In addition to the special organisation of objects and the provision of the necessary methods, the implementation of container classes requires the templating of objects.

Template classes or class templates are used when you want to create a class that depends on additional external parameters, which can be other classes or data types. For example, if you need to create a list class, you don't want to have to rewrite the list implementation for all possible element types. It would be nice to write one class with one parameter and get several specific list classes at once (character, integer, floating-point, user-defined type lists, etc.).
In C++, containers are part of the Standard Template Library (STL) for this very reason, along with iterators and some algorithms.

There are two main types of containers: sequence and associative containers. To find an element in sequence containers (`list`, `vector`, `array`, `stack`, `queue`), you have to look through the container one by one, while in associative containers (`map`, `set`, `multiset`) you just need to look through the key associated with the value.

## Information

- The program was developed in C++ language of C++17 standard using gcc compiler;
- The library code was located in the src folder.
- The program code written in Google style
- Iterators were used;
- Classes are template;
- Classes are implemented within the `my` namespace;
- Full coverage of library functions code with unit-tests using the GTest library