/**
 * Copyright 2007-2011 Jarbas Jácome
 *
 * This file is part of ViMus.
 *
 * ViMus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ViMus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ViMus.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "VimusMachine.h"

//Freenect::Freenect freenect; //KINECT

using namespace std;

/**
 * VimusMachine default constructor.
 */
VimusMachine :: VimusMachine ()
{
    if (DEBUG_MODE)
        cout << "\nVimusMachine constructed.";
}

/**
 * VimusMachine destructor.
 */
VimusMachine :: ~VimusMachine()
{
//    delete(kinect);
}

/**
 * Steady as she goes
 */
void VimusMachine :: start ()
{
    VideoCaptureOpenCV vidCap;
    vidCap.init();
    this->videoCap = &vidCap;
/* KINECT
    this->kinect = &freenect.createDevice<MyFreenectDevice>(0);
    this->kinect->startVideo();
	this->kinect->startDepth();
//*/
	this->editor = new VimusMachineEditor(this->videoCap);//, this->kinect);

	this->rootAbsObj = this->editor->getRootAbsObj();

}

void VimusMachine::stop()
{
//   	kinect->stopVideo();
//	kinect->stopDepth();

}

/**
 * Updates machine state.
 * Executes DSP Duty cicle.
 */
void VimusMachine :: update()
{
	this->rootAbsObj->update();
}

/**
 * Creates a new machine object.
 */
VimusGUIObject * VimusMachine :: createObject(const string& label, float posX,
												float posY, float posZ)
{
	return this->editor->createObject(label, posX, posY, posZ);
}

/**
 * Removes an object by index.
 */
void VimusMachine :: removeObject(int i)
{
	this->editor->removeObject(i);
}

/**
 * Connect objects pins.
 */
bool VimusMachine :: connectPins(int srcObj, int outPin, int dstObj, int inPin)
{
	return this->editor->connectPins(srcObj, outPin, dstObj, inPin);
}

/**
 * Disconnect objects pins.
 */
void VimusMachine :: disconnectPins(int srcObj, int outPin, int dstObj, int inPin)
{
	this->editor->disconnectPins(srcObj, outPin, dstObj, inPin);
}

/**
 * Set currentAbsObj by index.
 */
void VimusMachine :: setCurrentAbsObj(int index)
{
	this->editor->setCurrentAbsObj(index);
}

/**
 * Set currentAbsObj by son's name.
 */
void VimusMachine :: setCurrentAbsObj(const string& objName)
{
	this->editor->setCurrentAbsObj (objName);
}

/**
 * Set currentAbsObj to be the current cube's parent cube.
 */
void VimusMachine :: setCurrentAbsObjToParent()
{
	this->editor->setCurrentAbsObjToParent();
}

/**
 * Draws all OpenGL objects
 */
void VimusMachine:: drawOpenGLObjects()
{
    this->editor->drawOpenGLObjects();
}
