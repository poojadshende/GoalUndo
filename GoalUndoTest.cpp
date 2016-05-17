/**
 * Unit Tests for GoalUndo class
**/

#include <gtest/gtest.h>
#include "GoalUndo.h"
using namespace std;
class GoalUndoTest : public ::testing::Test
{
	protected:
		GoalUndoTest(){}
		virtual ~GoalUndoTest(){}
		virtual void SetUp(){}
		virtual void TearDown(){}
};

/*TEST(GoalUndoTest, sanityCheck)
{
	ASSERT_TRUE(true);
}*/

TEST(GoalUndoTest, add_operation_no_goal_exist)
{
	string str="line";
	GoalUndo gundo;
	gundo.addOperation(str);
	ASSERT_EQ(gundo.getGoal(), str);
}

TEST(GoalUndoTest, add_operation_to_mostRecently_goal)
{
	string str1="line", str2="extendLine", result=str1+" "+str2;
	GoalUndo gundo;
	gundo.addOperation(str1);
	gundo.addOperation(str2);
	ASSERT_EQ(gundo.getGoal(), str1);
	ASSERT_EQ(gundo.getOperations(), result);
	
}

TEST(GoalUndoTest, add_empty_operation)
{
	string emptyString="";
	string str1="line", str2="extendLine", result=str1+" "+str2;
	GoalUndo gundo;
	gundo.addOperation(str1);
	gundo.addOperation(str2);
	gundo.addOperation(emptyString);
	ASSERT_EQ(gundo.getGoal(), str1);
	ASSERT_EQ(gundo.getOperations(), result);
}

TEST(GoalUndoTest, add_new_op_within_new_goal)
{
	string str1="triangle", str2="baseLine";
	GoalUndo gundo;
	gundo.addOperation(str1, str2);
	ASSERT_EQ(gundo.getGoal(), str1);
	ASSERT_EQ(gundo.getOperations(), str2);
}

TEST(GoalUndoTest, add_new_op_with_empty_goal)
{
	string str1="", str2="baseLine";
	GoalUndo gundo;
	gundo.addOperation(str1, str2);
	ASSERT_EQ(gundo.getGoal(), str1);
	ASSERT_NE(gundo.getOperations(), str2);
}

TEST(GoalUndoTest, add_empty_op_within_new_goal)
{
	string str1="triangle", str2="";
	GoalUndo gundo;
	gundo.addOperation(str1, str2);
	ASSERT_NE(gundo.getGoal(), str1);
	ASSERT_EQ(gundo.getOperations(), str2);
}

TEST(GoalUndoTest, empty_goal)
{
	string str1="square", str2="side1", str3="side2", str4="side3", str5="side4";
	GoalUndo gundo;
	gundo.addOperation(str1, str2);	
	gundo.addOperation(str3);
	gundo.addOperation(str4);
	gundo.addOperation(str5);
	ASSERT_EQ(gundo.getGoal(), str1);
}
