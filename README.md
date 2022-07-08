<img src="Game/Textures/zote.png" alt="drawing" width="100"/>

# **Zote Engine**

Zote is a 2D Game Engine developed for my final university assignment. 
<br/><br/>

## Features
- Scene
- Camera (Orthographic and Perspective)
- Entities and Components
- 2D Rendering
- 2D Physics
- Scripting System
- Build System
- Input System
<br/><br/>

## Build
- Ensure you are using Windows 64-bit
- Ensure you have Visual Studio 2022 installed
- Clone this project
- Open the project's root folder
- Run `GenerateProjects.bat`
- Open `Zote.sln` and ✨Enjoy✨
<br/><br/>

## Hello Zote
<p></p>

### Window setup
Zote doesn't have an Editor yet. So if you want to create a brand new game some basic setup is required. In order to start writing code go to the Game project and open `Game.cpp`. Then, inside the `Run` method, create your first Window and call his `Init()` and `StartLoop()` methods.

```
Ref<Window> myWindow = MakeRef<Window>();
myWindow->Init();

//Your scene setup code goes HERE.

myWindow->StartLoop();
```

The window **must** be constructed as a reference. The `Ref` syntax is just a normal shared pointer. The `StartLoop()` method initialises the window loop. So if you write code after that function it won't execute until the Zote Window get's closed.
<p></p>
Running the application now should open an empty grey window.
<p></p>

### First entity
In order to create entites a `Scene` instance is required. At this point you **can't** create multiple scenes. After the scene initialisation you can call the scene `CreateEntity()` method and start adding components to it.

```
Scene myScene(myWindow);
Entity zote = myScene.CreateEntity();
zote.AddComponent<SpriteComponent>("Textures/zote.png");
```
<p></p>
At this point by running the application you should be experiencing the pleasure of being in the presence of Zote, a kinght of great renown.

<p></p>

## Script System
<p></p>

The script system is quite similar to the Unity Monobehiavours. Behind the scenes works with the ECS pattern but the usage is more simple. To start using scripts you must to add the `ScriptComponent` to your entity.

Then, you can create your script in new `.h` and `.cpp` separated files. The next example will show how to create a script that changes between two sprites:
<p></p>

`SwitchBetweenSprites.h`
```
#pragma once
#include <ZoteCommon.h>

using namespace Zote;

class SwitchBetweenSprites : public Script
{
public:
	cstr pathA = "";
	cstr pathB = "";
	float timeToSwitch = 0;

	void Start() override;
	void Update(float deltaTime) override;

private:
	Entity thisEntity;
	bool change = false;
	float currentTime = 0;

};
```
`SwitchBetweenSprites.cpp`
```
#include "SwitchBetweenSprites.h"

void SwitchBetweenSprites::Start()
{
	LOG("Script SwitchBetweenSprites started");
	thisEntity = GetEntity();
}

void SwitchBetweenSprites::Update(float deltaTime)
{
	auto& spriteComponent = thisEntity.GetComponent<SpriteComponent>();
	
	currentTime += deltaTime;

	if (currentTime < timeToSwitch)
		return;

    currentTime = 0;

	cstr path = change ? pathA : pathB;
	spriteComponent.AddTexture(path);
	change = !change;

    LOG("Sprite texture updated to: " << path);
}
```
When the script is ready go back to `Game.cpp` and don't forget to write the preprocessor statement, for this example: `#include "Scripts/SwitchBetweenSprites.h"`. By using the `AddScript()` method you can attach the script to the script component. It is possible to call this function with multiple scripts to attach them to a single Entity. It's mandatory to create the script instance as a **pointer**. This is the final code inside the `Run()` method.
```
Ref<Window> window = MakeRef<Window>();
window->Init();

Scene scene(window);

Entity myEntity = scene.CreateEntity();
myEntity.AddComponent<SpriteComponent>();
		
auto& myEntity_Scripts = myEntity.AddComponent<ScriptComponent>();
		
auto* switchScript = new SwitchBetweenSprites();
switchScript->pathA = "Textures/zote.png";
switchScript->pathB = "Textures/sus.png";
switchScript->timeToSwitch = 1;

myEntity_Scripts.AddScript(switchScript);

window->StartLoop();
```
By hitting the run button you should see the amogus and zote textures switching in the screen.
















 
