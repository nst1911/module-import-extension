# module-import-extension

`ModuleImportExtension` is a helper class used for `QJSEngine` to extend its functionality by adding  `importModule()` function in engine's global scope.

JavaScript modules allow you to break up your code into separate files. This makes it easier to maintain the code-base. 

JavaScript modules rely on the `import` and `export` statements. However, Qt Script does not support import statement and only provide a function `QJSEngine::importModule()`. That is, you can't import modules from your JS script code, only by using the C++ backend functionality.

`ModuleImportExtension` class inserts `importModule()` function in `QJSEngine` global scope that provides you import modules in the similar way like it is with JS import statement.

The example of importing modules with `ModuleImportExtension` is shown in **main.cpp**.

It is convenient to use because you have to insert only one file (**moduleimportextension.h**) in your project.
