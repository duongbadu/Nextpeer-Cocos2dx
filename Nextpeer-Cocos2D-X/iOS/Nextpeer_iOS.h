//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//

#ifndef ___NEXTPEER_IOS_H
#define ___NEXTPEER_IOS_H

#include "Export.h"
#include "stdint.h"
#include "CCNextpeer.h"
#include "Nextpeer/Nextpeer.h"

namespace nextpeer {
    
    /**
     Use the Nextpeer class to interface your application with the Nextpeer service.
     */
    class Nextpeer_iOS : public CCNextpeer
    {
    public:
		Nextpeer_iOS();
	
		/**
		 Set Nextpeer-Facebook bridge.
		 Should be invoked before initialize.
		 */
		virtual void setFacebookBridge(id<NPFacebookBridgeDelegate> bridge);

        /**
         Initializes the SDK using your app's parameters
         */
        virtual void initialize(const char* apiKey);

        /**
         Launches the Nextpeer Dashboard
         
         */
        void launchDashboard();
        
        /** @name Tournament managment */
        
        /**
         This method is used to push a buffer to the other players.
         This can potentially be used to create custom notifications or some other interactive mechanism that incorporates the other players.
         @param pBuffer. This is the buffer you wish to send to the other players
         @param length. The length of the buffer
         @note  The buffer will be sent to the other players and will activate the
         -(void)nextpeerDidReceiveTournamentCustomMessage: method on their NPTournamentDelegate delegate.
         */
        void pushDataToOtherPlayers(void * pBuffer, uint32_t length);
        

        /**
         This method is used to push a buffer to the other players using the unreliable data channel.
         This can potentially be used to create custom notifications or some other interactive mechanism that incorporates the other players.
         Note that there is no gurantee that this message will reach some or all the players.
         @param pBuffer. This is the buffer you wish to send to the other players
         @param length. The length of the buffer
         @note  The buffer will be sent to the other players and will activate the
         -(void)nextpeerDidReceiveUnreliableTournamentCustomMessage: method on their NPTournamentDelegate delegate.
         */
        void unreliablePushDataToOtherPlayers(void* pBuffer, uint32_t length);
        
        /**
         Call this method to report the current score for the tournament. This allows Nextpeer to send various notifications about the players' scores.
         
         */
        void reportScoreForCurrentTournament(uint32_t score);
        
        /**
         Call this method when your game manage the current tournament and the player just died (a.k.a. 'Last Man Standing').
         Nextpeer will call NextpeerDelegate's nextpeerDidTournamentEnd method after reporting the last score.
         
         @note: The method will act only if the current tournament is from 'GameControlled' tournament type
         */
        void reportControlledTournamentOverWithScore(uint32_t score);
        
        /**
         Call this method to check if any tournament is running at the moment.
         
         */
        bool isCurrentlyInTournament();
        
        /**
         Call this method when the user wishes to exit the current tournament.
         @note This will close any in-game notifiactions and dialogs.
         */
        void reportForfeitForCurrentTournament();
        
        /**
         This method will return the amount of seconds left for this tournament.
         @note: If no tournament is currently taking place then this method will return 0.
         */
        uint32_t timeLeftInTournament();
        
        /**
         This method will return the Nextpeer ID for the current player
         */
        std::string getCurrentPlayerId();
        
        /**
         This method will return the name of the current player
         */
        std::string getCurrentPlayerName();
        
        /**
         Call this method to enable or disable the in-game ranking display during a tournament. You can change this setting during a tournament (making the ranking display appear and disappear), but will not be animated.
         */
        void enableRankingDisplay(bool enableRankingDisplay);
        
        /**
         Call this method to change the score modifier of the giving recording. The modifier can be negative or positive and thus points will either
         be added or reduced from the recording's score.
         */
        virtual void reportScoreModifierForRecording(const char* recordingPlayerId, int32_t modifier);
        
        /**
         Call this method to pause the given recording.
         */
        virtual void requestPauseRecording(const char* recordingPlayerId);
        
        /**
         Call this method to resume the given recording.
         */
        virtual void requestResumeRecording(const char* recordingPlayerId);
        
        /**
         Call this method to stop the given recording.
         */
        virtual void requestStopRecording(const char* recordingPlayerId);
        
        /**
         Call this method to rewind the given recording by timeDelta milliseconds.
         */
        virtual void requestRewindRecording(const char* recordingPlayerId, uint32_t timeDelta);
        
        /**
         Call this method to fast forwad the given recording by timeDelta milliseconds.
         */
        virtual void requestFastForwardRecording(const char* recordingPlayerId, uint32_t timeDelta);
        
        /**
         Registers to a synchronized event.
         
         A synchronized event can be used to synchronize all players at a particular point in the game. For example, at the beginning of the game, each client may need to load resources, which takes variable time, depending on the player's device. The event will be fired (see [NPTournamentDelegate nextpeerDidReceiveSynchronizedEvent:withReason:]) either when everyone registered for it, or after the specified timeout, and all players will receive it at the same time.
         
         When working with synchronized events, you should be aware of the following edge cases:
         1. Clients who are too late to register to an event will not be notified of the event until they register.
         2. Recordings will pause when they register to an event that wasn't registered to by a real player, and will wait until the event is fired due the registration of a live player(s).
         3. Recordings that are late to register to an event will behave just as regular clients, and will continue their playback as usual.
         
         @param eventName The name of the synchronization event to register to.
         @param timeout The maximum amount of time to wait for all other participants to register for the sync event.
         */
        virtual void registerToSynchronizedEvent(const char* eventName, uint32_t timeout);
        
        /**
         Call this method to capture a specail moment in you game. A moment can be a new level, high score or any other special event in your game.
         */
        virtual void captureMoment();


        static Nextpeer_iOS* getInstance();
		
	private:
        static Nextpeer_iOS* _sharedInstance;
		id<NPFacebookBridgeDelegate> _facebookBridge;
    };
}


#endif // ___NEXTPEER_IOS_H