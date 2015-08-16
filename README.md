# OCScript
Original Command Script for C++  
It's assumed to be used for the game.

## Usage
### 1. Create a class that implements the ICommand
#### The following methods require to implement:
```C++
wstring GetCommandName();
void Access(AccessEventArgs *e, vector<wstring> params);
```
#### The following methods not require to implement:
```C++
void PreUpdate();
void Update();
```
[DetailSample](https://github.com/marihachi/OCScript/blob/master/src/OCScriptSample/src/Start.cpp#L6-L34).
## License
MIT License.