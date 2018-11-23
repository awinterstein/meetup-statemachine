#include "setup.hpp"
#include <boost/msm/back/state_machine.hpp>

// back-end
#include <boost/msm/back/state_machine.hpp>
//front-end
#include <boost/msm/front/state_machine_def.hpp>


using namespace std;
namespace msm = boost::msm;
namespace mpl = boost::mpl;

namespace example
{
    // events
    struct play {};
    struct end_pause {};
    struct stop {};
    struct pause {};
    struct open_close {};
    struct cd_detected {};
  

    // front-end: define the FSM structure 
    struct player_ : public msm::front::state_machine_def<player_>
    {
        template <class Event,class FSM>
        void on_entry(Event const& ,FSM&) 
        {
            HAL::DISPLAY::writeTopLine( "entering: Player");
        }
        template <class Event,class FSM>
        void on_exit(Event const&,FSM& ) 
        {
            HAL::DISPLAY::writeTopLine( "leaving: Player");
        }

        // The list of FSM states
        struct Empty : public msm::front::state<> 
        {
            // every (optional) entry/exit methods get the event passed.
            template <class Event,class FSM>
            void on_entry(Event const&,FSM& ) {HAL::DISPLAY::writeTopLine( "entering: Empty");}
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) {HAL::DISPLAY::writeTopLine( "leaving: Empty");}
        };
        struct Open : public msm::front::state<> 
        {	 
            template <class Event,class FSM>
            void on_entry(Event const& ,FSM&) {HAL::DISPLAY::writeTopLine( "entering: Open");}
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) {HAL::DISPLAY::writeTopLine( "leaving: Open");}
        };

        // sm_ptr still supported but deprecated as functors are a much better way to do the same thing
        struct Stopped : public msm::front::state<msm::front::default_base_state,msm::front::sm_ptr> 
        {	 
            template <class Event,class FSM>
            void on_entry(Event const& ,FSM&) {HAL::DISPLAY::writeTopLine( "entering: Stopped");}
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) {HAL::DISPLAY::writeTopLine( "leaving: Stopped");}
            void set_sm_ptr(player_* pl)
            {
                m_player=pl;
            }
            player_* m_player;
        };

        struct Playing : public msm::front::state<>
        {
            template <class Event,class FSM>
            void on_entry(Event const&,FSM& ) {HAL::DISPLAY::writeTopLine( "entering: Playing");}
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) {HAL::DISPLAY::writeTopLine( "leaving: Playing");}
        };

        // state not defining any entry or exit
        struct Paused : public msm::front::state<>
        {
        };

        // the initial state of the player SM. Must be defined
        typedef Empty initial_state;

        // transition actions
      void start_playback(play const&)       { HAL::DISPLAY::writeTopLine( "player::start_playback\n"); }
      void open_drawer(open_close const&)    { HAL::DISPLAY::writeTopLine( "player::open_drawer\n"); }
      void close_drawer(open_close const&)   { HAL::DISPLAY::writeTopLine( "player::close_drawer\n"); }
      void store_cd_info(cd_detected const&) { HAL::DISPLAY::writeTopLine( "player::store_cd_info\n"); }
      void stop_playback(stop const&)        { HAL::DISPLAY::writeTopLine( "player::stop_playback\n"); }
      void pause_playback(pause const&)      { HAL::DISPLAY::writeTopLine( "player::pause_playback\n"); }
      void resume_playback(end_pause const&) { HAL::DISPLAY::writeTopLine( "player::resume_playback\n"); }
      void stop_and_open(open_close const&)  { HAL::DISPLAY::writeTopLine( "player::stop_and_open\n"); }
      void stopped_again(stop const&)	{HAL::DISPLAY::writeTopLine( "player::stopped_again\n");}
      

        typedef player_ p; // makes transition table cleaner

        // Transition table for player
        struct transition_table : mpl::vector<
            //    Start     Event         Next      Action				 Guard
            //  +---------+-------------+---------+---------------------+----------------------+
          a_row < Stopped , play        , Playing , &p::start_playback                         >,
          a_row < Stopped , open_close  , Open    , &p::open_drawer                            >,
           _row < Stopped , stop        , Stopped                                              >,
            //  +---------+-------------+---------+---------------------+----------------------+
          a_row < Open    , open_close  , Empty   , &p::close_drawer                           >,
            //  +---------+-------------+---------+---------------------+----------------------+
          a_row < Empty   , open_close  , Open    , &p::open_drawer                            >,
          a_row < Empty   , cd_detected , Stopped , &p::store_cd_info    >,
          a_row < Empty   , cd_detected , Playing , &p::store_cd_info    >,
            //  +---------+-------------+---------+---------------------+----------------------+
          a_row < Playing , stop        , Stopped , &p::stop_playback                          >,
          a_row < Playing , pause       , Paused  , &p::pause_playback                         >,
          a_row < Playing , open_close  , Open    , &p::stop_and_open                          >,
            //  +---------+-------------+---------+---------------------+----------------------+
          a_row < Paused  , end_pause   , Playing , &p::resume_playback                        >,
          a_row < Paused  , stop        , Stopped , &p::stop_playback                          >,
          a_row < Paused  , open_close  , Open    , &p::stop_and_open                          >
            //  +---------+-------------+---------+---------------------+----------------------+
        > {};
      
        // Replaces the default no-transition response.
        template <class FSM,class Event>
        void no_transition(Event const& e, FSM&,int state)
        {
	  HAL::DISPLAY::writeTopLine( "no transition from state %d on event %s", state, typeid(e).name());
        }
    };
    // Pick a back-end
    typedef msm::back::state_machine<player_> player;

    //
    // Testing utilities.
    //
    static char const* const state_names[] = { "Stopped", "Open", "Empty", "Playing", "Paused" };
    void pstate(player const& p)
    {
      HAL::DISPLAY::writeTopLine( " -> %s",  state_names[p.current_state()[0]]);
    }

    void test()
    {        
		player p;
        // needed to start the highest-level SM. This will call on_entry and mark the start of the SM
        p.start(); 
        // go to Open, call on_exit on Empty, then action, then on_entry on Open
        p.process_event(open_close()); pstate(p);
        p.process_event(open_close()); pstate(p);
        // will be rejected, wrong disk type
        p.process_event(
            cd_detected()); pstate(p);
        p.process_event(
            cd_detected()); pstate(p);
		p.process_event(play());

        // at this point, Play is active      
        p.process_event(pause()); pstate(p);
        // go back to Playing
        p.process_event(end_pause());  pstate(p);
        p.process_event(pause()); pstate(p);
        p.process_event(stop());  pstate(p);
        // event leading to the same state
        // no action method called as it is not present in the transition table
        p.process_event(stop());  pstate(p);
        HAL::DISPLAY::writeTopLine( "stop fsm");
        p.stop();
    }
}



int main()
{
  example::test();
  return 0;
}
