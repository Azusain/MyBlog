---
title: C++ 类型转换
date: 2023/8/12 23:57
categories: 
- C/C++
tags:
- C/C++
---

在 C++ 中，`static_cast`、`dynamic_cast` 和普通类型转换（C 风格的类型转换）都可以用来进行类型转换，但它们之间有一些重要的区别。

`static_cast` 用于在相关类型之间进行转换，例如基类和派生类之间的指针或引用，或者隐式转换。它在编译时执行，不执行运行时检查。这意味着如果您尝试执行无效的转换，编译器可能不会报错，但运行时行为是未定义的。

`dynamic_cast` 用于在多态类型之间进行安全的向下转换。它在运行时执行类型检查，以确保转换是有效的。如果转换失败，则返回空指针（对于指针）或抛出 `std::bad_cast` 异常（对于引用）。由于 `dynamic_cast` 需要运行时类型信息（RTTI），因此它比 `static_cast` 更慢。

普通类型转换（C 风格的类型转换）是 C++ 中最原始的类型转换方式。它可以执行多种类型转换，包括 `static_cast`、`const_cast` 和 `reinterpret_cast`。然而，由于它不执行运行时检查，并且容易滥用，因此不建议在 C++ 程序中使用。

总之，当您需要在相关类型之间进行转换时，应该使用 `static_cast`；当您需要在多态类型之间进行安全的向下转换时，应该使用 `dynamic_cast`；而普通类型转换（C 风格的类型转换）应该尽量避免使用。

希望这些信息对您有所帮助！

