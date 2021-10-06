#include "pch.h"
#include "CppUnitTest.h"
<<<<<<< HEAD
#include "../GameStaticLib/World.h"
#include <iostream>
using namespace std;
=======
#include "../GameStaticLib/Player.h"
#include "../GameStaticLib/Player.cpp"
>>>>>>> develop

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
<<<<<<< HEAD
	TEST_CLASS(WorldGeneration)
	{
	public:
		
		TEST_METHOD(Load)
		{
			string nameFile = "test.txt";
			string testText = "textodeprueba";
			World world = World(nameFile);
			Assert::AreEqual(world.Load(nameFile), testText);
			
=======
	TEST_CLASS(TestPlayer)
	{
	public:
		
		TEST_METHOD(TestGetId)
		{
			Player player = Player(2);
			Assert::IsTrue(player.GetId() == 2);
>>>>>>> develop
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
}
