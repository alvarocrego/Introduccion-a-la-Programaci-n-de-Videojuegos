/**	Definition of the class Super Ship

Class Prefix: CBS_

@author Ramon Molla
@version 2011-01-11
*/


#ifndef CBS_BOSS
#define CBS_BOSS

#include <ExplosiveChar.h>
#include <SIMessage.h>

//Definitions for the game
#define CBS_MAX_FILE_NAME		 25
#define CBS_MAX_HEALTH			500 //Maximun amount of health of a given Supply Ship by default
#define CBS_MAX_HIT_DURATION	500

#define CBS_MAX_X_SHIFT			  4

#define CBS_SHOOT_SPEED		  0.017f

/** \typedef CBS_EXTRA_TIMERS

*	Types of different local timing managed by any supplyship
*/
typedef enum {
	CBS_UPD_PERIOD,
	CBS_RND_PERIOD,
	CBS_MAX_TIMERS
} CBS_EXTRA_TIMERS;

typedef enum {
	CBS_NO_BOSS, ///For management purpouses
	CBS_BOSS_,
	CBS_BIG_BOSS,	//Super powerful supply ship. More health, bigger and can launch ships from inside. Only in 3D mode
	CBS_MAXTYPE
} CBS_TYPE;

///Artificial Intelligence
///Different states for the FSMs that control the SS behaviour
typedef enum {
	CBS_UNBORN = 0,	///For management purpouses only
	CBS_BORN,		///The character is just born but it is not still operative (living)
	CBS_LIVING,		///Everything this character may do while it is alive 
	CBS_DYING,		///The character has been touched so many times that its life has gone negative. So it has to burst before being died. Starts an explosion and dies
	CBS_DEAD,		///The character is no operative. Reached after dying
	CBS_MAXSTATE	///For management purpouses only
} CBS_BOSS_STATE;	///Generic character possible states that can be any character by default

						///Different transitions for the FSMs that control the SS behaviour
typedef enum {
	CBS_DEFAULT = 0,				///For management purpouses only
	CBS_BORNING,				///The character is just borning. Passing from UNBORN to BORN states
	CBS_GETTING_ALIVE,			///Passing from BORN to LIVING states
	CBS_MOVING,					///Remaining in LIVING state while moving the Supply Ship
	CBS_DISPLAYING,				///Remaining in LIVING state while displaying the Supply Ship
	CBS_HEALTHING,				///Remaining in LIVING state while increasing the health of the Supply Ship
	CBS_BURST,					///The character has been touched so many times that its life has gone negative. So it has to burst. Passing from LIVING to DYING states
	CBS_DIE,					///The character is no operative. Reached after dying
	CBS_FINISHED,				///The character is no operative. Reached after the game has finished: player has lost or win the level or game is exited
	CBS_RESURRECTING,			///Passing to Unborn state
	CBS_MAXTRANSITION			///For management purpouses only
} CBS_BOSS_TRANSITIONS;	///Generic character possible states that can be any character by default

								///The ships that contains the captain of the enemy navy. They are moving over the whole navy. It has a different geometry
class CBoss : public CExplosiveChar
{
	//Attributes
public:
	//RT-DESK
	double		timeRTdeskMsg;		//Tiempo Mensaje RTDESK
	cMsgNavy	*msg;
	cMsgNavy	*msgUpd;			//RTDESK Message Time

									//Methods
	void Init();
	void CBoss::InitTransforms();

	//AI Methods
	///Increasing health while time passes by
	void AI_Healthing();
	///Moving the Supply Ship
	void AI_Move();
	///The supply ship is going to burst before being dead
	void AI_Die();
	///What to do when the supply ship is dead
	void AI_Death();
	bool OutEvent(CBS_BOSS_TRANSITIONS EventName);

	//Physics
	void Collided(CCharacter *CollidedChar);

	///Shows the supplyship on the screen
	void Render(void);
	///Change the way the supplyship is going to be rendered on the screen
	void ChangeRenderMode(CHAR_RENDER_MODE Mode);

	void Update(void);
	void DiscreteUpdate(void);

	void ReceiveMessage(RTDESK_CMsg *pMsg);

	///Constructor of the class
	CBoss();
	~CBoss() {}
};

//External methods to use with the class internal FSM
///Called everytime a time slot happens and its health has to be increased
void *CBS_FSM_Healthing(LPSTR *args, CBoss *Boss);
///Called everytime a time slot happens and a moving has to be done
void *CBS_FSM_Move(LPSTR *args, CBoss *Boss);
///Called when the supply ship is going to burst before dying
void *CBS_FSM_Dye(LPSTR *args, CBoss *Boss);
void *CBS_FSM_Dying(LPSTR *args, CBoss *Boss);
void *CBS_FSM_Death(LPSTR *args, CBoss *Boss);
///Called when the supply ship passed from death to unborn states
void *CBS_FSM_Unborning(LPSTR *args, CBoss *Boss);
///ACHTUNG: Temporalmente. Cambiar en el futuro
void *CBS_display(LPSTR *args, CBoss *Boss);

#endif