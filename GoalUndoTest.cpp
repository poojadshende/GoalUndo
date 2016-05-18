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

TEST(GoalUndoTest, add_operation_emptyGoals)
{
	string str="line";
	GoalUndo gundo;
	gundo.addOperation(str);
	ASSERT_EQ(gundo.getGoal(), str);
}

TEST(GoalUndoTest, add_operation_to_mostRecentGoal)
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

TEST(GoalUndoTest, add_newOp_within_newGoal)
{
	string str1="triangle", str2="baseLine";
	GoalUndo gundo;
	gundo.addOperation(str1, str2);
	ASSERT_EQ(gundo.getGoal(), str1);
	ASSERT_EQ(gundo.getOperations(), str2);
}

TEST(GoalUndoTest, add_newOp_with_emptyGoal)
{
	string str1="", str2="baseLine";
	GoalUndo gundo;
	gundo.addOperation(str1, str2);
	ASSERT_EQ(gundo.getGoal(), str1);
	ASSERT_NE(gundo.getOperations(), str2);
}

TEST(GoalUndoTest, add_emptyOp_within_newGoal)
{
	string str1="triangle", str2="";
	GoalUndo gundo;
	gundo.addOperation(str1, str2);
	ASSERT_NE(gundo.getGoal(), str1);
	ASSERT_EQ(gundo.getOperations(), str2);
}

TEST(GoalUndoTest, check_undoGoal_nonEmptyGoal)
{
	string str1="square", str2="side1", str3="side2", str4="side3", str5="side4";
	GoalUndo gundo;
	gundo.addOperation(str1, str2);	
	gundo.addOperation(str3);
	gundo.addOperation(str4);
	gundo.addOperation(str5);
	gundo.undoGoal();
	ASSERT_EQ(gundo.getGoal(), "");
	ASSERT_EQ(gundo.getOperations(), "");		
}

TEST(GoalUndoTest, check_undoGoal_emptyGoals)
{
	string str1="triangle", str2="";
	GoalUndo gundo;
	gundo.addOperation(str1, str2);
	gundo.undoGoal();
	ASSERT_EQ(gundo.getGoal(), "");
}

TEST(GoalUndoTest, check_undoOperation_goal_with_multipleOperations)
{
	string str1="square", str2="side1", str3="side2", str4="side3", str5="side4";
	string result1=str2+" "+str3+" "+str4;
	GoalUndo gundo;
	gundo.addOperation(str1, str2);	
	gundo.addOperation(str3);
	gundo.addOperation(str4);
	gundo.addOperation(str5);
	gundo.undoOperation();
	ASSERT_EQ(gundo.getGoal(), str1);
	ASSERT_EQ(gundo.getOperations(), result1);
	gundo.undoOperation(str4);
	gundo.undoOperation(str3);
	ASSERT_EQ(gundo.getGoal(), str1);
	ASSERT_EQ(gundo.getOperations(), str2);
}

TEST(GoalUndoTest, check_undoOperation_goal_with_oneOperation)
{
	string goal="circle", op1="radius", newGoal="line", newOp="";
	GoalUndo gundo;
	gundo.undoOperation();
	gundo.addOperation(goal, op1);
	gundo.addOperation(newGoal, newOp);
	gundo.undoOperation();
	ASSERT_EQ(gundo.getGoal(), "");
	ASSERT_EQ(gundo.getOperations(), "");
}


TEST(GoalUndoTest, remove_given_operation)
{
	string goal1="square", op1="side1", op2="side2", op3="side3";
	string goal2="triangle", opr1="side1", opr2="side2";
	string result=op1+" "+op2+" "+op3;
	GoalUndo gundo;
	gundo.undoOperation("side2");
	gundo.addOperation(goal1, op1);	
	gundo.addOperation(op2);
	gundo.addOperation(op3);
	gundo.addOperation(goal2, opr1);
	gundo.addOperation(opr2);	
	
	gundo.undoOperation("side2");
	ASSERT_EQ(gundo.getGoal(), goal2);
	ASSERT_EQ(gundo.getOperations(), opr1);	
	gundo.undoGoal();
	ASSERT_EQ(gundo.getGoal(), goal1);
	ASSERT_EQ(gundo.getOperations(), result);
	
}

TEST(GoalUndoTest, remove_givenOperation_oneGoal_oneOperation)
{
	string goal1="rectanle", op1="side1";
	GoalUndo gundo;
	gundo.addOperation(goal1, op1);	
	
	gundo.undoOperation(op1);
	ASSERT_EQ(gundo.getGoal(), "");
}

TEST(GoalUndoTest, remove_givenOperation_opDoesNotExist)
{
	string goal1="rectanle", op1="side1";
	GoalUndo gundo;
	gundo.addOperation(goal1, op1);	
	
	gundo.undoOperation("side2");
	ASSERT_EQ(gundo.getGoal(), goal1);
	ASSERT_EQ(gundo.getOperations(), op1);	
}

