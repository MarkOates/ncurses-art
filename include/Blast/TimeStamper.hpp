#pragma once


#include <string>


namespace Blast
{
   class TimeStamper
   {
   private:

   public:
      TimeStamper();
      ~TimeStamper();

      std::string generate_now_timestamp_utc();
   };
}



