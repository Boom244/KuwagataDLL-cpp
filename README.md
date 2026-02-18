![KuwagataDLL-C++](https://github.com/Boom244/KuwagataDLL-cpp/blob/master/Kuwagata-Logo.png "KuwagataDLL-C++")

## What is this?
This is a rewrite the backend of a C# project I published on GitHub in 2022, *Kuwagata*, in C++. I've also given some of the code a facelift, decreased the sizes of some functions, and rewritten some out-right. I plan to continue to improve this project over time, in order to make Kuwagata (and any other projects dependent on this DLL) faster and more memory-efficient. 

## Why do this?
I plan to port this functionality to OBS Studio out-right as a plugin later on. Rewriting the core functionality in an unmanaged language like C++ also allows me to develop more streaming client specific plugins later on, while consolidating core functionality in one project. 

## What if I want to contribute?
Contributions are welcome! I plan to include a style doc for them later on, but as of now, I welcome any and all code help, because I, admittedly, know a lot less about C++ than I should.


# Relevant Credits
This library was made possible with the use of the testing library [Unity by ThrowTheSwitch](https://github.com/ThrowTheSwitch/Unity), alongside [Niels Lohmann's JSON parser for C++.](https://github.com/nlohmann/json)

This library also makes use of the JSON schema and regular expressions from [Nathan Patton](https://github.com/avendesora)'s project, [PythonBible](https://github.com/avendesora/pythonbible). 
