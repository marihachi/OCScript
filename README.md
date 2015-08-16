# OCScript
Original Command Script for C++  
It's assumed to be used for the game.

## Usage
### 1. Create a class that implements the ICommand
#### Require implementation Methods
```C++
wstring GetCommandName(); // コマンド名を設定します
void Access(AccessEventArgs *e, vector<wstring> params); // コマンドの実行タイミングに呼ばれます
```
#### Not require implementation Methods
```C++
void PreUpdate(); // Update より前のタイミングに呼ばれます
void Update(); // 更新のタイミングに呼ばれます
```
[DetailSample](https://github.com/marihachi/OCScript/blob/master/src/OCScriptSample/src/Start.cpp#L6-L34).
## License
MIT License.