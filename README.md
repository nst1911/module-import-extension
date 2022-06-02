# module-import-extension

## Brief

`ModuleImportExtension` is a helper class used for `QJSEngine` to extend its functionality by adding a module import function in engine's global scope. This function allows to import JS modules in runtime while evaluating a script.

## Description

JavaScript modules allow you to break up your code into separate files. This makes it easier to maintain the code-base. 

JavaScript modules rely on the `import` and `export` statements. However, Qt Script does not support import statement and only provide a function `QJSEngine::importModule()`. That is, you can't import modules from your JS script code, only by using the C++ backend functionality.

`ModuleImportExtension` class inserts a module import function in `QJSEngine` global scope that provides you import modules in the similar way like it is with JS import statement.

## Example

The script **module.js** is the example of a module. 

The script **main.js** uses a function `importModule()` to import **module.js**. The first argument is a relative path to the module, the second argument is an alias for the module space.

If you want to run the project succesfully, you have to put all **.js** files in an application's current directory (`build-moduleimportextension-Desktop_Qt....`)

The example of importing modules with `ModuleImportExtension` is shown in **main.cpp**.

It is convenient to use because you have to insert only one file (**moduleimportextension.h**) in your project.
