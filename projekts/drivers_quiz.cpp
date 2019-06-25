#include "Projekt2.h"

#include <algorithm>
#include <ctime>

#include "Question.hpp"
#include "Quiz.hpp"


#define INITIALIZE "INITIALIZE"
#define GUESS_ANSWER "GUESS_ANSWER"
#define ROTATE_QUESTION "ROTATE_QUESTION"
#define MOVE_MENU_DOWN "MOVE_MENU_DOWN"
#define MOVE_MENU_UP "MOVE_MENU_UP"
#define OPEN_IMAGE "OPEN_IMAGE"


int current_question_index = -1;
bool quiz_finished = false;

Quiz quiz;


Question get_current_question()
{
   return quiz.get_questions()[current_question_index];
}


void set_quiz_questions(Quiz &q)
{
   q.set_questions({
         { "The speed limit approaching a school crosswalk is",
           "",
           "15 mph",
           { "20 mph", "25 mph" }
         },
         { "A school bus is stopped on a four-lane road with its stop-sign arm extended, you must:",
           "",
           "Stop regardless of your direction of travel",
           { "Slow down and proceed with caution", "Stop if you are moving in the same direction of travel" }
        },
         { "All arrived at an uncontrolled intersection at the same time. Which has the right-of-way?",
           "Test1Q3.jpg",
           "Car 3",
           { "Car 2", "Car 1" }
        },
         { "When you see or hear an emergency vehicle approaching",
           "",
           "Immediately drive to the right side of the road and stop",
           { "Slow down and permit the emergency vehicle to pass", "Remain alert and stay to the right" }
        },
         { "This hand signal means",
           "Test1Q5.jpg",
           "Stopping or slowing",
           { "Right turn", "Left turn" }
        },
         { "You should give the right-of-way to any pedestrian who is",
           "",
           "Crossing any street",
           { "In a marked crosswalk", "In any crosswalk or intersection" }
        },
         { "When driving on wet roads you should",
           "",
           "Reduce your speed",
           { "Pump your brakes occasionally", "Switch to low beam headlights" }
        },
         { "Before entering a road from an alley or driveway, you must",
           "",
           "Stop before reaching the sidewalk",
           { "Flash your high beam headlights", "Sound your horn" }
        },
         { "When backing, you should",
           "",
           "Turn and look out the rear window",
           { "Look in your inside rearview mirror", "Turn and look out the driver window" }
        },
         { "The car that made the correct turn was",
           "Test1Q10.jpg",
           "Car 3",
           { "Car 2", "Car 1" }
        },
///////// question 11:
         { "If you are parking uphill and there is a curb, you should",
           "",
           "Turn your wheels to the left, away from the curb",
           { "Turn your wheels to the right, toward the curb", "Keep your wheels straight ahead" }
        },
         { "When no speed limit is posted, the maximum speed in a business or residential area is",
           "",
           "25 mph",
           { "30 mph", "35 mph" }
        },
         { "A yellow line in the middle of the road means",
           "",
           "Two-way traffic",
           { "One-way traffic", "School zone" }
        },
         { "If you intend to turn beyond an intersection, you should",
           "",
           "Wait to signal your turn until you are in the intersection",
           { "Signal your turn as you approach the intersection", "Use a hand signal" }
        },
         { "It is illegal to follow fire vehicles traveling in response to an alarm, within",
           "",
           "500 feet",
           { "200 feet", "300 feet" }
        },
         { "If you approach a school bus that is picking up or dropping off children, you must",
           "Test1Q16.jpg",
           "Stop until the bus is moving or the stop sign arm is no longer extended",
           { "Stop and then proceed with caution", "Slow and yield the right-of-way to all pedestrians" }
        },
         { "This hand signal means",
           "Test1Q17.jpg",
           "Left turn",
           { "Right turn", "Stopping or slowing down" }
        },
         { "It is safe to return to your lane after passing when",
           "Test1Q18.jpg",
           "You can see both headlights of the vehicle in your inside rearview mirror",
           { "The driver you just passed signals you over", "When you can see the driver in your side mirror" }
        },
         { "If you are parking downhill, you should",
           "",
           "Turn your wheels to the right, toward the edge of the road",
           { "Turn your wheels to the left, away from the edge of the road", "Keep your wheels straight ahead" }
        },
         { "Before you make a turn, use your turn signals",
           "",
           "For at least 4 seconds",
           { "Only when other vehicles can be seen on the road", "For at least 500 feet" }
        },
////////////// Question 21:
         { "It is illegal to park if a crosswalk is within",
           "",
           "20 feet",
           { "10 feet", "15 feet" }
        },
         { "Before you turn, you must signal continuously for at least",
           "",
           "100 feet",
           { "50 feet", "75 feet" }
        },
         { "This hand signal means",
           "Test1Q23.jpg",
           "Right turn",
           { "Stopping or slowing down", "Left turn" }
        },
         { "The wheelchair symbol in a parking space means that it is reserved for disabled persons",
           "Test1Q24.jpg",
           "With no exceptions",
           { "But may be used by any driver if no other space is available", "But may be used by any driver for loading and unloading" }
        },
         { "The white car will turn left. The black car will go straight. Which has the right-of-way?",
           "Test1Q25.jpg",
           "Black car",
           { "White car", "Neither car" }
        },
         { "To make a left turn, you should turn into",
           "Test1Q26.jpg",
           "Lane 2",
           { "Lane 1", "Either lane 1 or lane 2" }
        },
         { "It is illegal to park if a fire hydrant is within",
           "",
           "15 feet",
           { "5 feet", "10 feet" }
        },
         { "A school bus with flashing lights has stopped on a divided highway. Who must stop?",
           "Test1Q28.jpg",
           "Cars 2 and 3",
           { "Cars 1 and 2", "Car 1 only" }
        },
         { "If you are parking uphill and there is no curb, you should",
           "",
           "Turn your wheels to the right, toward the edge of the road",
           { "Turn your wheels to the left, away from the edge of the road", "Keep your wheels straight ahead" }
        },
         { "This sign means",
           "Test1Q30.jpg",
           "Slippery when wet",
           { "Curves ahead", "Hill ahead" }
        },
/////////////////////////////
///////// QUIZ 2!! //////////
/////////////////////////////
         { "A sign with this shape means",
           "Test2Q1.jpg",
           "Speed and direction regulation",
           { "Yield right-of-way", "Railroad crossing" }
        },
         { "A red painted curb means you may",
           "",
           "Not stop, stand or park",
           { "Stop to load or unload only", "Stop to pick up or drop off passengers only" }
        },
         { "A green lighted arrow on a traffic light means you may",
           "",
           "Proceed in the direction of the arrow without stopping",
           { "Not proceed in the direction of the arrow", "Proceed in the direction of the arrow after you have come to a complete stop" }
        },
         { "A sign with this shape means",
           "Test2Q4.jpg",
           "Warning",
           { "Railroad crossing", "Yield right-of-way" }
        },
         { "You are approaching an intersection where the lighted arrow has just changed to yellow",
           "",
           "You must stop and wait for the light to turn green",
           { "You may turn only if you can clear the intersection before the light changes to red", "You should slow down and turn with caution" }
        },
         { "Unless prohibited by a sign, a left turn on red is permitted",
           "",
           "From a one-way road to a one-way road",
           { "Except in school zones", "From a two-way road to a one-way road" }
        },
         { "This sign means",
           "Test2Q7.jpg",
           "U-turn is not permitted",
           { "Left turn is not permitted", "Wrong Way" }
        },
         { "A broken yellow line in the middle of the road means",
           "",
           "Passing is permitted in either direction",
           { "No passing is permitted in either direction", "School zone" }
        },
         { "This sign means",
           "Test2Q9.jpg",
           "School crossing",
           { "Pedestrians prohibited", "Pedestrian crossing" }
        },
         { "This sign means",
           "Test2Q10.jpg",
           "Divided highway ends",
           { "Lane ends ahead", "Divided highway begins" }
        },
///// T2 : Question 11:
         { "A flashing red traffic light at an intersection means the",
           "",
           "Same as a Stop sign",
           { "Same as a Stop light", "Light is about to turn green" }
        },
         { "A sign with this shape means",
           "Test2Q12.jpg",
           "Railroad warning",
           { "Stop", "Speed and direction regulation" }
        },
         { "A yellow line in the middle of the road means",
           "",
           "Two-way traffic",
           { "School zone", "One-way traffic" }
        },
         { "This sign means",
           "Test2Q14.jpg",
           "No left turn permitted",
           { "Road turns sharply to the left", "Left lane must turn left" }
        },
         { "A broken yellow line alongside a solid yellow line in the middle of the road means",
           "",
           "You may pass if the broken line is on your side",
           { "You may pass if the solid line is on your side", "No passing is permitted in either direction" }
        },
         { "A sign with this shape means",
           "Test2Q16.jpg",
           "Yield right-of-way",
           { "Speed limit", "Stop" }
        },
         { "This sign means",
           "Test2Q17.jpg",
           "Pedestrian crossing",
           { "School crossing", "Construction workers ahead" }
        },
         { "You are approaching an intersection where the traffic light has just changed to yellow",
           "",
           "You must stop and wait for the light to change to green",
           { "You should slow down and proceed with caution", "You may proceed only if you can clear the intersection before the light changes to red" }
        },
         { "This sign means",
           "Test2Q19.jpg",
           "No right turn permitted",
           { "Road turns sharply to the right", "Left lane must turn right" }
        },
         { "This sign means",
           "Test2Q20.jpg",
           "Two-way traffic",
           { "Divided highway begins", "Two lanes ahead" }
        },
//////// T2 : Question 21:
         { "A broken white line in the middle of the road means",
           "",
           "Traffic on both sides is moving in the same direction",
           { "No passing in either direction", "Traffic is moving in opposite directions" }
        },
         { "This sign means",
           "Test2Q22.jpg",
           "Traffic merging",
           { "Lane ends", "Left lane must go straight" }
        },
         { "A flashing red traffic light at an intersection means you must",
           "",
           "Stop, check for traffic, then proceed with caution",
           { "Slow down, check for traffic, then proceed with caution", "Stop and wait for the light to change to green" }
        },
         { "A sign with this shape means",
           "Test2Q24.jpg",
           "No passing zone",
           { "Railroad crossing", "Right turn permitted on red" }
        },
         { "A sign with this shape means",
           "Test2Q25.jpg",
           "Stop",
           { "Railroad crossing", "Yield right-of-way" }
        },
         { "A right turn on red is allowed",
           "",
           "Except where prohibited by a sign",
           { "Only where indicated by a sign", "Only on a divided road" }
        },
         { "A flashing yellow light at an intersection means you must",
           "",
           "Slow down, check for traffic, then proceed with caution",
           { "Stop and wait for the light to change to green", "Stop, check for traffic, then proceed with caution" }
        },
         { "This sign means",
           "Test2Q28.jpg",
           "You may turn left or go straight",
           { "Divided highway", "Merging traffic" }
        },
         { "A red lighted arrow on a traffic light means",
           "",
           "Stop and wait for the arrow to change to green before turning",
           { "Stop, check for traffic and turn with caution", "No turn permitted" }
        },
         { "A double, solid yellow line in the middle of the road means",
           "",
           "No passing in either direction",
           { "Curve ahead", "You are permitted to pass" }
        },
/////////////////////////////
///////// QUIZ 3!! //////////
/////////////////////////////
         { "When following a vehicle at night, lower your high beam headlights when you are within",
           "",
           "200 feet",
           { "100 feet", "300 feet", "400 feet", "750 feet", "500 feet" }
        },
         { "When entering a freeway, you should not",
           "Test3Q2.jpg",
           "Cross a solid line",
           { "Use your turn signal", "Match the speed of the traffic in the right lane" }
        },
         { "To avoid the glare from oncoming headlights",
           "",
           "Glance back and forth between the side of the road and straight ahead",
           { "Focus your eyes on the center line of the road", "Focus your eyes on the side of the road" }
        },
         { "If your vehicle begins to hydroplane you should",
           "",
           "Release the accelerator",
           { "Pump the brakes", "Pull off the road immediately and slow down gradually" }
        },
         { "You should avoid the right lane of the freeway during rush hour",
           "",
           "To leave room for vehicles entering and exiting",
           { "To allow emergency vehicles to pass", "Because it is the most likely place for accidents" }
        },
         { "Switch to low beams when oncoming traffic is within",
           "",
           "500 feet",
           { "750 feet", "300 feet", "200 feet", "100 feet", "400 feet" }
        },
         { "When driving on wet roads you should",
           "",
           "Reduce your speed",
           { "Pump your breaks occasionally", "Switch to low beam headlights" }
        },
         { "If you have a tire blowout",
           "",
           "Do not brake, but slow down and pull off the road",
           { "Pump the brakes rapidly and pull off the road", "Turn the wheel in the direction of the skid" }
        },
         { "If you drive in fog, you should turn on the",
           "",
           "Low beam headlights",
           { "High beam headlights", "Parking lights" }
        },
         { "If you come upon a severe dust storm, you should",
           "",
           "Reduce speed and pull off the road",
           { "Turn on your headlights", "Maintain your speed and don’t change lanes" }
        },
///// test 3: question 11
         { "When you merge on the freeway, you should be driving",
           "",
           "At the same speed as the traffic in the right lane",
           { "About 10 mph slower than the speed limit", "At the legal speed limit on the freeway" }
        },
         { "The best way to bring your vehicle out of a skid is to",
           "",
           "Turn the wheel in the direction of the skid",
           { "Turn the wheel away from the direction of the skid", "Pump the brakes" }
        },
         { "If you are in the black car, the most difficult car for you to see is",
           "Test3Q13.jpg",
           "Car 2",
           { "Car 3", "Car 1" }
        },
         { "You should leave enough space between you and the vehicle directly in front of you",
           "",
           "To allow for a sudden stop",
           { "To stay out of the other driver's blind spot", "So the other driver can see both your headlights in the rearview mirror" }
        },
         { "When changing lanes, check your side mirrors for other traffic and",
           "",
           "Turn your head quickly and look over your shoulder",
           { "Check the inside rearview mirror", "Slow down by at least one third" }
        },
         { "To keep aware of the position of traffic behind you, it is best to",
           "",
           "Check your rearview mirror often",
           { "Turn your head and look out the rear window", "Create a space cushion around you" }
        },
         { "The driver of this vehicle has a \"blind spot\" in",
           "Test3Q17.jpg",
           "Areas 1 and 3",
           { "Area 2", "Areas 1 and 2" }
        },
         { "Normally, the distance from you to the vehicle ahead should be at least equivalent",
           "",
           "3 seconds",
           { "5 seconds", "2 seconds" }
        },
         { "If you come to an intersection and your view to the side is blocked, you should",
           "",
           "Stop, then inch forward until you can see clearly in both directions",
           { "Maintain speed and look both ways", "Slow down and look both ways" }
        },
///// test 3: question 21
         { "Penalties for the first conviction for driving under the influence are",
           "",
           "10 days jail, $1,250, alcohol treatment, community service and ignition interlock",
           { "90 days jail, $3,000, alcohol treatment, community service and ignition interlock", "30 days jail, $1,500, alcohol treatment, community service and ignition interlock" }
        },
         { "Penalties for the second conviction for driving under the extreme influence are",
           "",
           "120 days jail, $3,250, 1 year revocation, alcohol treatment, community service and ignition interlock",
           { "30 days jail, $750, 1 year revocation, alcohol treatment, community service and ignition interlock", "60 days jail, $1,500, 90 day suspension, alcohol treatment, community service and ignition interlock" }
        },
         { "You are driving under the influence if your blood alcohol concentration is",
           "",
           "0.08% or above (0.04 if the vehicle requires a commercial license)",
           { "0.10% or above (0.04 if the vehicle requires a commercial license)", "0.80% or above (0.40 if the vehicle requires a commercial license)" }
        },
         { "If under age 21, your license may be suspended if your blood alcohol concentration is",
           "",
           "Any amount",
           { "0.05% or above", "0.10% or above" }
        },
         { "You are driving under the extreme influence if your blood alcohol concentration is",
           "",
           "0.15% or above",
           { "0.28% or above", "0.18% or above" }
        },
         { "Bicyclists should",
           "",
           "Ride with the flow of traffic",
           { "Ride facing traffic", "Ride on the sidewalk" }
        },
         { "When passing a bicycle traveling in the same direction, leave a distance of at least",
           "",
           "3 feet",
           { "10 feet", "6 feet" }
        },
         { "Bicyclists must",
           "",
           "Obey the same traffic laws as motor vehicles",
           { "Stay in the right lane at all times", "Never pass motor vehicles" }
        },
         { "It is illegal to follow fire vehicles traveling in response to an alarm, within",
           "",
           "500 feet",
           { "300 feet", "200 feet" }
        },
         { "If you are parking uphill and there is no curb, you should",
           "",
           "Turn your wheels to the right, toward the edge of the road",
           { "Turn your wheels to the left, away from the edge of the road", "Keep your wheels straight ahead" }
        },
   });

   quiz.shuffle_questions();
}


#include <iostream>


void initialize()
{
   init_color(21, (int)(175.0/255.0*1000), 0, (int)(255.0/255.0*1000));
   init_pair(3, COLOR_BLACK, 21);

   create_text("question", 20, 8);
   create_menu("answers", 30, 12).set_styles(COLOR_PAIR(3));

   create_text("status", 30, 5, 0.5);

   mappings['\n'] = GUESS_ANSWER;
   mappings['j'] = MOVE_MENU_DOWN;
   mappings['k'] = MOVE_MENU_UP;
   mappings['o'] = OPEN_IMAGE;

   events[INITIALIZE] = []{
      set_quiz_questions(quiz);
      current_question_index = -1;
      quiz_finished = false;
      emit_event(ROTATE_QUESTION);
   };
   events[ROTATE_QUESTION] = []{
      current_question_index++;
      int current_correct_answer_num = rand() % 3;

      auto current_question = get_current_question();

      std::vector<std::string> answers = current_question.get_incorrect_answers();
      answers.push_back(current_question.get_correct_answer());
      std::random_shuffle(answers.begin(), answers.end());

      find_text("question").set_text(current_question.get_question());
      find_menu("answers").set_options(answers);

      std::stringstream question_notification;
      question_notification << "Question " << (current_question_index+1) << " of " << quiz.get_questions().size();
      find_text("status").set_text(question_notification.str());
   };
   events[MOVE_MENU_UP] = []{
      find_menu("answers").move_cursor_up();
   };
   events[MOVE_MENU_DOWN] = []{
      find_menu("answers").move_cursor_down();
   };
   events[OPEN_IMAGE] = []{
      auto current_question = get_current_question();
      std::string image_filename = current_question.get_image_filename();
      if (image_filename == "") find_text("status").set_text("No image!");
      else
      {
         std::stringstream command;
         command << "open ./bin/images/" << image_filename;
         system(command.str().c_str());
      }
   };
   events[GUESS_ANSWER] = []{
      auto current_question = get_current_question();
      auto guessed_answer = find_menu("answers").current_selection();

      if (current_question.get_correct_answer() != guessed_answer) emit_event("CRASH!!");

      if (current_question_index == (quiz.get_questions().size()-1))
      {
         quiz_finished = true;
         find_text("status").set_text("FINISHED!");
      }
      else emit_event(ROTATE_QUESTION);
   };

   emit_event(INITIALIZE);
}


