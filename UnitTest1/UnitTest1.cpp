#include "pch.h"
#include "CppUnitTest.h"
#include "../GameStaticLib/World.h"
#include <iostream>
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(WorldGeneration)
	{
	public:
		
		TEST_METHOD(Load)
		{
			string nameFile = "test.txt";
			string testText = "texto de prueba";
			World world = World(nameFile);
			Assert::AreEqual(world.Load(nameFile), testText);
			
		}
	};
}
