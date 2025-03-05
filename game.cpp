#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#include "LogManager.h"
#include "Clock.h"
#include "GameManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "Event.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "Frame.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "Box.h"
#include "utility.h"
#include "Music.h"
#include "Sound.h"
#include "ViewObject.h"

#include "Reticle.h"
#include "Fish.h"
#include "GameStart.h"

using namespace df;

//void runAllTests();

int main(int argc, char *argv[])
{
	// GameManager startup.
	GM.startUp();

	LM.setFlush(true);

	RM.loadSprite("sprites/ff-spr-background.txt", "background");
	RM.loadSprite("sprites/ff-spr-shadow.txt", "shadow");
	RM.loadSprite("sprites/ff-spr-castbar.txt", "castbar");
	RM.loadSprite("sprites/ff-spr-lure.txt", "lure");
	RM.loadSprite("sprites/ff-spr-lure-hit.txt", "lure-hit");
	RM.loadSprite("sprites/ff-spr-guppy.txt", "guppy");
	RM.loadSprite("sprites/ff-spr-boot.txt", "boot");
	RM.loadSprite("sprites/ff-spr-ampersalmon.txt", "ampersalmon");
	RM.loadSprite("sprites/ff-spr-eel.txt", "eel");
	RM.loadSprite("sprites/ff-spr-bluefish.txt", "bluefish");
	RM.loadSprite("sprites/ff-spr-flounder.txt", "flounder");
	RM.loadSprite("sprites/ff-spr-yellowfin.txt", "yellowfin");
	



	// Set world boundaries to 80 horizontal, 24 vertical.
	WM.setBoundary(Box(Vector(0,0),80,24));

	// Set view to 80 horizontal, 24 vertical.
	WM.setView(Box(Vector(0,0),80,24));

	Object* background = new Object();
	background -> setSolidness(SPECTRAL);
	background -> setAltitude(0);
	background -> setSprite("background");
	background -> setPosition(Vector(40,12));

	new Reticle();
	new Fish();
	new Fish();
	new Fish();

	// TODO: needs a sprite and background music
	//new GameStart();
	
	// Game loop test.
	GM.run();

	// GameManager shutdown.
	GM.shutDown();
}

/*
bool testLogManagerOutput();
bool testClockTiming();
bool testVectorObject();
bool testObjectList();
bool testEvent();
bool testEventStep();
bool testEventHandling();
bool testWorldManager();
bool testDisplayManager();
bool testInputManager();
bool testFrame();
bool testSprite();
bool testResourceManager();
bool testBox();
bool testViews();
bool testAudio();
bool testToString();

void runAllTests()
{
	LM.setFlush(true);

	if (testLogManagerOutput())
	{
		LM.writeLog("\nPASS: LogManager output test");
	}
	else
	{
		LM.writeLog("\nFAIL: LogManager output test");
	}

	if (testClockTiming())
	{
		LM.writeLog("\nPASS: Clock timing test");
	}
	else
	{
		LM.writeLog("\nFAIL: Clock timing test");
	}

	if (testVectorObject())
	{
		LM.writeLog("\nPASS: Vector and Object test");
	}
	else
	{
		LM.writeLog("\nFAIL: Vector and Object test");
	}

	if (testObjectList())
	{
		LM.writeLog("\nPASS: ObjectList test");
	}
	else
	{
		LM.writeLog("\nFAIL: ObjectList test");
	}

	if (testEvent())
	{
		LM.writeLog("\nPASS: Event test");
	}
	else
	{
		LM.writeLog("\nFAIL: Event test");
	}

	if (testEventStep())
	{
		LM.writeLog("\nPASS: EventStep test");
	}
	else
	{
		LM.writeLog("\nFAIL: EventStep test");
	}

	if (testEventHandling())
	{
		LM.writeLog("\nPASS: Event handling test");
	}
	else
	{
		LM.writeLog("\nFAIL: Event handling test");
	}

	if (testWorldManager())
	{
		LM.writeLog("\nPASS: WorldManager test");
	}
	else
	{
		LM.writeLog("\nFAIL: WorldManager test");
	}

	if (testDisplayManager())
	{
		LM.writeLog("\nPASS: DisplayManager test");
	}
	else
	{
		LM.writeLog("\nFAIL: DisplayManager test");
	}

	if (testInputManager())
	{
		LM.writeLog("\nPASS: InputManager test");
	}
	else
	{
		LM.writeLog("\nFAIL: InputManager test");
	}

	if (testFrame())
	{
		LM.writeLog("\nPASS: Frame test");
	}
	else
	{
		LM.writeLog("\nFAIL: Frame test");
	}

	if (testSprite())
	{
		LM.writeLog("\nPASS: Sprite test");
	}
	else
	{
		LM.writeLog("\nFAIL: Sprite test");
	}

	if (testResourceManager())
	{
		LM.writeLog("\nPASS: ResourceManager test");
	}
	else
	{
		LM.writeLog("\nFAIL: ResourceManager test");
	}

	if (testBox())
	{
		LM.writeLog("\nPASS: Box test");
	}
	else
	{
		LM.writeLog("\nFAIL: Box test");
	}

	if (testViews())
	{
		LM.writeLog("\nPASS: View test");
	}
	else
	{
		LM.writeLog("\nFAIL: View test");
	}

	if (testAudio())
	{
		LM.writeLog("\nPASS: Audio test");
	}
	else
	{
		LM.writeLog("\nFAIL: Audio test");
	}

	if (testToString())
	{
		LM.writeLog("\nPASS: toString test");
	}
	else
	{
		LM.writeLog("\nFAIL: toString test");
	}

	LM.writeLog("\n");
	LM.setFlush(false);
}

bool testLogManagerOutput()
{
	// LogManager output tests.
	LM.writeLog("\nLogManager output tests.");
	
	// Testing printf formatting.
	LM.writeLog("Testing %d, %d, %d, %s", 1, 2, 3, "testing");
	LM.writeLog("Pi is approximately %.2f", 3.14159);

	return true;
}

bool testClockTiming()
{
	// Clock timing tests. Appears to always return 1 millisecond over.
	LM.writeLog("\nClock timing tests.");

	timeBeginPeriod(1);

	// Testing delta and split accuracy.
	Clock clock;
	Sleep(20);
	LM.writeLog("Milliseconds slept for: %d", clock.delta());
	Sleep(20);
	LM.writeLog("Milliseconds slept for: %d", clock.delta());
	Sleep(20);
	LM.writeLog("Milliseconds slept for: %d", clock.split());
	Sleep(20);
	LM.writeLog("Milliseconds slept for: %d", clock.split());
	Sleep(20);
	LM.writeLog("Milliseconds slept for: %d", clock.delta());
	Sleep(3000);
	LM.writeLog("Milliseconds slept for: %d", clock.delta());
	timeEndPeriod(1);

	return true;
}

bool testVectorObject()
{
	// Vector and Object tests.
	LM.writeLog("\nVector and Object tests.");

	Object object;
	// Tests the getId() function.
	if (object.getId() != 0)
	{
		return false;
	}
	LM.writeLog("Object 1 id: %d", object.getId());

	// Tests that id increments.
	Object object2;
	if (object2.getId() != 1)
	{
		return false;
	}
	LM.writeLog("Object 2 id: %d", object2.getId());

	// Tests the getPosition() and getX() functions.
	if (object.getPosition().getX() != 0)
	{
		return false;
	}
	LM.writeLog("Object 1 x: %f", object.getPosition().getX());

	object.setPosition(Vector(3,4));
	// Tests the setPosition() and getMagnitude() functions.
	if (object.getPosition().getX() != 3 || object.getPosition().getMagnitude() != 5)
	{
		return false;
	}
	LM.writeLog("Object 1 new x: %f", object.getPosition().getX());
	LM.writeLog("Object 1 magnitude: %f", object.getPosition().getMagnitude());

	object2.setPosition(Vector(3,1));
	Vector sum = object.getPosition() + object2.getPosition();
	// Tests Vector addition.
	if (sum.getX() != 6 || sum.getY() != 5)
	{
		return false;
	}
	LM.writeLog("Object 1 + Object 2: %f, %f", sum.getX(), sum.getY());

	return true;
}

bool testObjectList()
{
	// ObjectList tests.
	LM.writeLog("\nObjectList tests.");

	ObjectList objectList;

	// Tests the isEmpty() function.
	if (objectList.isEmpty())
	{
		LM.writeLog("ObjectList empty");
	}
	else
	{
		return false;
	}

	Object object;
	Object object2;

	// Tests the remove object function.
	if (objectList.remove(&object) == -1)
	{
		LM.writeLog("ObjectList empty, so failed to remove.");
	}
	else
	{
		return false;
	}

	// Tests the insert object function.
	if (objectList.insert(&object) == -1)
	{
		return false;
	}
	if (objectList.insert(&object2) == -1)
	{
		return false;
	}
	// Tests the getCount() function.
	if (objectList.getCount() != 2)
	{
		return false;
	}
	LM.writeLog("ObjectList count: %d", objectList.getCount());

	// Tests the index operator.
	if (objectList.remove(objectList[1]) == -1)
	{
		return false;
	}
	if (objectList.getCount() != 1)
	{
		return false;
	}
	LM.writeLog("ObjectList count: %d", objectList.getCount());
	
	for (int i=0; i<999; i++)
	{
		objectList.insert(&object);
	}
	// Tests the isFull() function.
	if (objectList.isFull())
	{
		LM.writeLog("ObjectList full");
	}
	else
	{
		return false;
	}

	// Tests that an object cannot be inserted when the ObjectList is full.
	if (objectList.insert(&object) == -1)
	{
		LM.writeLog("ObjectList full, so failed to insert.");
	}
	else
	{
		return false;
	}

	objectList.clear();
	// Tests the clear function.
	if (objectList.getCount() != 0)
	{
		return false;
	}
	LM.writeLog("ObjectList cleared: %d", objectList.getCount());

	// Out of range, will throw an exception.
	//objectList.remove(objectList[-1]);
	//objectList.remove(objectList[0]);

	WM.removeObject(&object);
	WM.removeObject(&object2);

	return true;
}

bool testEvent()
{
	// Event tests.
	LM.writeLog("\nEvent tests.");

	Event event;
	// Tests the getType() function.
	if (event.getType() != "df::undefined")
	{
		return false;
	}
	LM.writeLog("Event type: %s", event.getType().c_str());

	event.setType("TestEvent");
	// Tests the setType() function.
	if (event.getType() != "TestEvent")
	{
		return false;
	}
	LM.writeLog("Event type: %s", event.getType().c_str());

	return true;
}

bool testEventStep()
{
	// EventStep tests.
	LM.writeLog("\nEventStep tests.");

	EventStep eventStep;
	// Tests that EventStep has a different type than default Events.
	if (eventStep.getType() != "df::step")
	{
		return false;
	}
	LM.writeLog("EventStep type: %s", eventStep.getType().c_str());

	// Tests the EventStep setType() function.
	eventStep.setType("Test StepEvent");
	if (eventStep.getType() != "Test StepEvent")
	{
		return false;
	}
	LM.writeLog("EventStep type: %s", eventStep.getType().c_str());

	// Tests the getStepCount() function.
	if (eventStep.getStepCount() != 0)
	{
		return false;
	}
	LM.writeLog("Step count: %d", eventStep.getStepCount());

	eventStep.setStepCount(2);
	// Tests the setStepCount() function.
	if (eventStep.getStepCount() != 2)
	{
		return false;
	}
	LM.writeLog("Step count: %d", eventStep.getStepCount());

	return true;
}

bool testEventHandling()
{
	// Event handling tests.
	LM.writeLog("\nEvent handling tests.");

	Saucer saucer;
	Event event;
	EventStep eventStep;
	// Tests that eventHandler does not handle the default Event.
	if (saucer.eventHandler(&event) == -1)
	{
		LM.writeLog("Default event not handled.");
	}
	else
	{
		return false;
	}

	eventStep.setType(STEP_EVENT);
	// Tests that eventHandler handles EventStep.
	if (saucer.eventHandler(&eventStep) == -1)
	{
		return false;
	}

	WM.removeObject(&saucer);

	return true;
}

bool testWorldManager()
{
	// WorldManager tests.
	LM.writeLog("\nWorldManager tests.");

	Object object;
	Object object2;
	Saucer saucer;

	WM.removeObject(&object2);

	// Tests the getAllObjects() and objectsOfType() functions.
	if (WM.getAllObjects().getCount() != 2 || WM.objectsOfType("Saucer").getCount() != 1 || WM.objectsOfType("Player").getCount() != 0)
	{
		return false;
	}
	LM.writeLog("Total objects in WorldManager: %d", WM.getAllObjects().getCount());
	LM.writeLog("Saucers found in WorldManager: %d", WM.objectsOfType("Saucer").getCount());
	LM.writeLog("Players found in WorldManager (none): %d", WM.objectsOfType("Player").getCount());

	WM.removeObject(&object);
	WM.removeObject(&saucer);

	new Saucer();
	// Tests the markForDelete() function.
	if (WM.markForDelete(WM.getAllObjects()[0]) == -1)
	{
		return false;
	}
	WM.update();

	new Saucer();
	new Saucer();
	new Saucer();

	ObjectList list = WM.objectsOfType("Saucer");
	for (int i=0; i<list.getCount(); i++)
	{
		// Tests more deletion.
		if (WM.markForDelete(list[i]) == -1)
		{
			return false;
		}
	}
	WM.update();

	// Tests that update() properly deleted all Objects.
	if (WM.getAllObjects().getCount() != 0)
	{
		return false;
	}
	LM.writeLog("Total objects in WorldManager: %d", WM.getAllObjects().getCount());

	return true;
}

bool testDisplayManager()
{
	// DisplayManager tests.
	LM.writeLog("\nDisplayManager tests.");

	// Tests window size functions.
	if (DM.getHorizontalPixels() != 1024 || DM.getVerticalPixels() != 768 || DM.getHorizontal() != 80 || DM.getVertical() != 24)
	{
		return false;
	}
	LM.writeLog("Window's horizontal distance (pixels): %d", DM.getHorizontalPixels());
	LM.writeLog("Window's vertical distance (pixels): %d", DM.getVerticalPixels());
	LM.writeLog("Window's horizontal distance (characters): %d", DM.getHorizontal());
	LM.writeLog("Window's vertical distance (characters): %d", DM.getVertical());

	// Tests drawing functions.
	DM.drawCh(Vector(10,10), 'a', YELLOW);
	DM.drawString(Vector(20,20), "hello", LEFT_JUSTIFIED, MAGENTA);
	DM.drawString(Vector(20,21), "hello", CENTER_JUSTIFIED, GREEN);
	DM.drawString(Vector(20,22), "hello", RIGHT_JUSTIFIED, CYAN);
	DM.drawString(Vector(50,15), "This is a long sentence.", LEFT_JUSTIFIED, WHITE);
	DM.getWindow() -> display();
	Sleep(3000);

	return true;
}

bool testInputManager()
{
	// InputManager tests.
	LM.writeLog("\nInputManager tests.");

	int count = 0;
	
	while (count < 1000)
	{
		IM.getInput(true);
		count++;
	}
	return true;
}

bool testFrame()
{
	// Frame tests.
	LM.writeLog("\nFrame tests.");

	Frame frame = Frame(4, 2, "hi");
	if (frame.getHeight() != 2 || frame.getWidth() != 4 || frame.getString() != "hi")
	{
		return false;
	}
	LM.writeLog("Frame width: %d", frame.getWidth());
	LM.writeLog("Frame height: %d", frame.getHeight());
	LM.writeLog("Frame string: %s", frame.getString().c_str());

	frame.setHeight(3);
	frame.setWidth(3);
	frame.setString("bye");

	if (frame.getHeight() != 3 || frame.getWidth() != 3 || frame.getString() != "bye")
	{
		return false;
	}
	LM.writeLog("Frame width: %d", frame.getWidth());
	LM.writeLog("Frame height: %d", frame.getHeight());
	LM.writeLog("Frame string: %s", frame.getString().c_str());


	frame.setString("longframee");
	frame.draw(Vector (10,5), GREEN);

	Frame frame2 = Frame(2, 1, "hi");
	frame2.draw(Vector (2,2), YELLOW);

	Frame frame3 = Frame(2, 4, "uh oh");
	frame3.draw(Vector (5,2), MAGENTA);

	DM.getWindow() -> display();
	Sleep(3000);

	return true;
}

bool testSprite()
{
	// Sprite tests.
	LM.writeLog("\nSprite tests.");

	Sprite sprite = Sprite(2);

	sprite.setHeight(3);
	sprite.setWidth(3);
	sprite.setLabel("test");
	sprite.setColor(YELLOW);

	if (sprite.getHeight() != 3 || sprite.getWidth() != 3 || sprite.getLabel() != "test" || sprite.getColor() != YELLOW)
	{
		return false;
	}
	LM.writeLog("Sprite width: %d", sprite.getWidth());
	LM.writeLog("Sprite height: %d", sprite.getHeight());
	LM.writeLog("Sprite label: %s", sprite.getLabel().c_str());

	sprite.addFrame(Frame(3,2,"a1"));
	sprite.addFrame(Frame(3,2,"b2"));
	sprite.addFrame(Frame(3,2,"c3"));
	sprite.getFrame(2);
	LM.writeLog(sprite.getFrame(1).getString().c_str());

	sprite.draw(0, Vector (12,7));
	
	DM.getWindow() -> display();
	Sleep(3000);

	return true;
}

bool testResourceManager()
{
	// ResourceManager tests.
	LM.writeLog("\nResourceManager tests.");

	if (RM.loadSprite("sprites/saucer-spr.txt", "saucer") == -1)
	{
		return false;
	}

	if (RM.getSprite("saucer") -> getColor() != GREEN)
	{
		return false;
	}

	if (RM.unloadSprite(RM.getSprite("saucer") -> getLabel()) == -1)
	{
		return false;
	}

	if (RM.loadSprite("sprites/saucer-spr-malformed.txt", "saucer-malformed") == 0)
	{
		return false;
	}

	if (RM.loadSprite("sprites/saucer-spr-malformed2.txt", "saucer-malformed2") == 0)
	{
		return false;
	}

	if (RM.loadSprite("sprites/saucer-spr-malformed3.txt", "saucer-malformed3") == 0)
	{
		return false;
	}

	return true;
}

bool testBox()
{
	// Box tests.
	LM.writeLog("\nBox tests.");

	Box box = Box(Vector(3,4), 5, 6);

	if (box.getCorner().getMagnitude() != 5 || box.getHorizontal() != 5 || box.getVertical() != 6)
	{
		return false;
	}
	LM.writeLog("Box corner coordinates: %f, %f", box.getCorner().getX(), box.getCorner().getY());
	LM.writeLog("Box width: %f", box.getHorizontal());
	LM.writeLog("Box height: %f", box.getVertical());

	box.setCorner(Vector(6,8));
	box.setHorizontal(2);
	box.setVertical(1);
	if (box.getCorner().getMagnitude() != 10 || box.getHorizontal() != 2 || box.getVertical() != 1)
	{
		return false;
	}
	LM.writeLog("Box corner coordinates: %f, %f", box.getCorner().getX(), box.getCorner().getY());
	LM.writeLog("Box width: %f", box.getHorizontal());
	LM.writeLog("Box height: %f", box.getVertical());

	// Bounding box tests.
	Saucer saucer;
	saucer.setBox(Box(Vector(5,12), 3, 4));
	saucer.getBox();
	if (saucer.getBox().getCorner().getMagnitude() != 13 || saucer.getBox().getHorizontal() != 3 || saucer.getBox().getVertical() != 4)
	{
		return false;
	}
	LM.writeLog("Saucer's bounding box corner coordinates: %f, %f", saucer.getBox().getCorner().getX(), saucer.getBox().getCorner().getY());
	LM.writeLog("Saucer's bounding box width: %f", saucer.getBox().getHorizontal());
	LM.writeLog("Saucer's bounding box height: %f", saucer.getBox().getVertical());

	// Box intersection tests.
	Box box2 = Box(Vector(0,0), 5, 5);
	Box box3 = Box(Vector(0,0), 1, 1);
	if (utility::boxIntersectBox(box2, box3) == false)
	{
		return false;
	}

	box3.setCorner(Vector(3,3));
	box3.setHorizontal(3);
	box3.setVertical(3);
	if (utility::boxIntersectBox(box2, box3) == false)
	{
		return false;
	}

	return true;
}

bool testViews()
{
	// View tests.
	LM.writeLog("\nView tests.");

	WM.setView(Box(Vector(2,2),1,1));
	if (WM.getView().getCorner().getX() != 2)
	{
		return false;
	}

	return true;
}

bool testAudio()
{
	// Audio tests.
	LM.writeLog("\nAudio tests.");
		
	RM.loadSound("sounds/fire.wav", "sound");
	RM.getSound("sound") -> play(true);
	Sleep(3000);
	RM.getSound("sound") -> stop();
	
	RM.unloadSound("sound");

	RM.loadMusic("sounds/start-music.wav", "music");
	RM.getMusic("music") -> play();

	Sleep(1000);
	RM.getMusic("music") -> pause();
	
	Sleep(1000);
	RM.getMusic("music") -> play();
	
	Sleep(1000);
	RM.getMusic("music") -> stop();

	RM.unloadMusic("music");

	RM.loadSound("sounds/fakepath.wav", "fake");

	return true;
}

bool testToString()
{
	// toString tests.
	LM.writeLog("\ntoString tests.");

	if (utility::toString(0) != "0")
	{
		return false;
	}

	if (utility::toString(2) != "2")
	{
		return false;
	}

	return true;
}
*/