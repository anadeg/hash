#include "pch.h"
#include "CppUnitTest.h"
#include "..\aois6\inner_adressing.h"
#include "..\aois6\inner_adressaing.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(add_to_hash)
		{
			hash_table ht;
			ht.add("abc", "hsdf");

			std::string info = "\nid: abc\ndata: hsdf\nkey: 78\ncollision: 0\nused: 1\ndeleted: 0\nnext: -1";

			std::string test = ht.print_searched_element("abc");

			Assert::IsTrue(info == test);
		}
		TEST_METHOD(add_to_hash_collision)
		{
			hash_table ht;
			ht.add("abc", "hsdf");
			ht.add("bca", "hudf");
			ht.add("iii", "hsdf");

			std::string info1 = "\nid: abc\ndata: hsdf\nkey: 78\ncollision: 1\nused: 1\ndeleted: 0\nnext: 0";
			std::string info2 = "\nid: bca\ndata: hudf\nkey: 78\ncollision: 1\nused: 1\ndeleted: 0\nnext: -1";
			std::string info3 = "\nid: iii\ndata: hsdf\nkey: 624\ncollision: 0\nused: 1\ndeleted: 0\nnext: -1";

			std::string test1 = ht.print_searched_element("abc");
			std::string test2 = ht.print_searched_element("bca");
			std::string test3 = ht.print_searched_element("iii");

			Assert::IsTrue(info1 == test1);
			Assert::IsTrue(info2 == test2);
			Assert::IsTrue(info3 == test3);
		}
		TEST_METHOD(add_to_hash_repeating)
		{
			hash_table ht;
			ht.add("ghr", "hsdf");
			ht.add("ghr", "hsdf");

			std::string info1 = "\nid: ghr\ndata: hsdf\nkey: 780\ncollision: 0\nused: 1\ndeleted: 0\nnext: -1";

			std::string test1 = ht.print_searched_element("ghr");

			Assert::IsTrue(info1 == test1);

			double percents = ht.fill_coefficient();
			Assert::AreEqual(percents, 0.04);
		}
		TEST_METHOD(add_to_hash_big_collision)
		{
			hash_table ht;

			ht.add("yoi", "hsdf");
			ht.add("oiy", "kwnx");//collision
			ht.add("ioy", "qmsa");//collision
			ht.add("tde", "amxl");//collision
			ht.add("aai", "kajs");

			std::string info1 = "\nid: yoi\ndata: hsdf\nkey: 1196\ncollision: 1\nused: 1\ndeleted: 0\nnext: 0";
			std::string info2 = "\nid: oiy\ndata: kwnx\nkey: 1196\ncollision: 1\nused: 1\ndeleted: 0\nnext: 1";
			std::string info3 = "\nid: ioy\ndata: qmsa\nkey: 1196\ncollision: 1\nused: 1\ndeleted: 0\nnext: 2";
			std::string info4 = "\nid: tde\ndata: amxl\nkey: 676\ncollision: 1\nused: 1\ndeleted: 0\nnext: -1";
			std::string info5 = "\nid: aai\ndata: kajs\nkey: 208\ncollision: 0\nused: 1\ndeleted: 0\nnext: -1";

			std::string test1 = ht.print_searched_element("yoi");
			std::string test2 = ht.print_searched_element("oiy");
			std::string test3 = ht.print_searched_element("ioy");
			std::string test4 = ht.print_searched_element("tde");
			std::string test5 = ht.print_searched_element("aai");

			Assert::IsTrue(info1 == test1);
			Assert::IsTrue(info2 == test2);
			Assert::IsTrue(info3 == test3);
			Assert::IsTrue(info4 == test4);
			Assert::IsTrue(info5 == test5);
		}
		TEST_METHOD(find_not_existing)
		{
			hash_table ht;
			ht.add("ghr", "hsdf");
			ht.add("ghr", "hsdf");

			std::string info1 = "no such element";

			std::string test1 = ht.print_searched_element("adax");

			Assert::IsTrue(info1 == test1);
		}
		TEST_METHOD(find_existing_collision_not_last)
		{
			hash_table ht;

			ht.add("yoi", "hsdf");
			ht.add("oiy", "kwnx");//collision
			ht.add("ioy", "qmsa");//collision
			ht.add("tde", "amxl");//collision
			ht.add("aai", "kajs");

			std::string info2 = "\nid: oiy\ndata: kwnx\nkey: 1196\ncollision: 1\nused: 1\ndeleted: 0\nnext: 1";

			std::string test2 = ht.print_searched_element("oiy");

			Assert::IsTrue(info2 == test2);
		}
		TEST_METHOD(find_existing_collision_last)
		{
			hash_table ht;

			ht.add("yoi", "hsdf");
			ht.add("oiy", "kwnx");//collision
			ht.add("aai", "kajs");

			std::string info1 = "\nid: oiy\ndata: kwnx\nkey: 1196\ncollision: 1\nused: 1\ndeleted: 0\nnext: -1";

			std::string test1 = ht.print_searched_element("oiy");

			Assert::IsTrue(info1 == test1);
		}
		TEST_METHOD(delete_collision_1)
		{
			hash_table ht;

			ht.add("yoi", "hsdf");
			ht.add("oiy", "kwnx");//collision
			ht.add("ioy", "qmsa");//collision
			ht.add("tde", "amxl");//collision
			ht.add("aai", "kajs");

			ht.del("oiy");

			std::string info2 = "\nid: oiy\ndata: kwnx\nkey: 1196\ncollision: 1\nused: 0\ndeleted: 1\nnext: 1";

			std::string test2 = ht.print_searched_element("oiy");

			Assert::IsTrue(info2 == test2);
		}
		TEST_METHOD(delete_collision_2)
		{
			hash_table ht;

			ht.add("yoi", "hsdf");
			ht.add("oiy", "kwnx");//collision
			ht.add("ioy", "qmsa");//collision
			ht.add("tde", "amxl");//collision
			ht.add("aai", "kajs");

			ht.del("tde");

			std::string info2 = "\nid: tde\ndata: amxl\nkey: 676\ncollision: 1\nused: 0\ndeleted: 1\nnext: -1";

			std::string test2 = ht.print_searched_element("tde");

			Assert::IsTrue(info2 == test2);
		}
		TEST_METHOD(delete_collision_3)
		{
			hash_table ht;

			ht.add("yoi", "hsdf");
			ht.add("oiy", "kwnx");//collision
			ht.add("ioy", "qmsa");//collision
			ht.add("tde", "amxl");//collision
			ht.add("aai", "kajs");

			ht.del("yoi");

			std::string info2 = "\nid: yoi\ndata: hsdf\nkey: 1196\ncollision: 1\nused: 0\ndeleted: 1\nnext: 0";

			std::string test2 = ht.print_searched_element("yoi");

			Assert::IsTrue(info2 == test2);
		}
		TEST_METHOD(delete_collision_4)
		{
			hash_table ht;

			ht.add("yoi", "hsdf");
			ht.add("oiy", "kwnx");//collision
			ht.add("ioy", "qmsa");//collision
			ht.add("tde", "amxl");//collision
			ht.add("aai", "kajs");

			ht.del("aai");

			std::string info2 = "\nid: aai\ndata: kajs\nkey: 208\ncollision: 0\nused: 0\ndeleted: 1\nnext: -1";

			std::string test2 = ht.print_searched_element("aai");

			Assert::IsTrue(info2 == test2);
		}
		TEST_METHOD(delete_collision_5)
		{
			hash_table ht;

			ht.add("yoi", "hsdf");
			ht.add("oiy", "kwnx");//collision
			ht.add("ioy", "qmsa");//collision
			ht.add("tde", "amxl");//collision
			ht.add("aai", "kajs");

			ht.del("asa");

			std::string info2 = "\nno such element";

			std::string test2 = ht.print_searched_element("asa");

			Assert::IsTrue(info2 == test2);
		}
	};
}
