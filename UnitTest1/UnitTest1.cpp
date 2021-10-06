#include "pch.h"
#include "CppUnitTest.h"
#include "../GameStaticLib/Player.h"
#include "../GameStaticLib/Player.cpp"
#include "../GameStaticLib/World.h"
#include <iostream>
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(TestPlayer)
	{
	public:
		
		TEST_METHOD(TestGetId)
		{
			Player player = Player(2);
			Assert::IsTrue(player.GetId() == 2);
		}

		TEST_METHOD(TestGetCoins)
		{
			Player player = Player(1);
			player.AddCoin();
			Assert::IsTrue(player.GetCoins() == 1);
		}

		TEST_METHOD(TestAddCoins)
		{
			Player player = Player(1);
			player.AddCoin();
			player.AddCoin();
			player.AddCoin();
			Assert::IsTrue(player.GetCoins() == 3);
			
			
		}

	};
	TEST_CLASS(WorldGeneration)
	{
		TEST_METHOD(Load)
		{
			string nameFile = "test.txt";
			string testText = "textodeprueba";
			World world = World(nameFile);
			
		}

	};
}
