# Object Oriented Monads

It's educational project, made with one purpose - teach students Functional Programming.  
`Monad` is one of key concept in Functional Programming and quite usefull in software engineering in general.

It simplifies **Error** handling and reduce branching by hiding them inside their implementation.  
And another piece of good news is that the special monadic operator substantially reduces the amount of brackets.  
With **Monads** you can turn this:

```c++
auto o1 = Option<int>(5);

if (o1.is_value()) {
 auto o2 = o1.transform([](auto x){...});
 if (o2.is_value()) {
  auto o3 = o2.transform([](auto x){...});
   if (o3.is_value()) {
    auto o4 = o3.transform([](auto x){...});
    //
    // infinite number of transforms
    //
   } else {
    // handle error
   }
 } else {
  // handle error
 }
} else {
 // handle error
}

```

Into this:

```c++
// >> here is '>>=' from Haskell
o1 >> div_m(2.0) >> filter_m(10) >> add_m(3.0) >> show_m(); // Val 5.5
```

If you're not even a student but have problems understanding, feel free to contact me for explanation.
