#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include <nac.h>
#include <nwrk.h>

#include "cli/input.h"
#include "cli/display.h"

#include "core/log.h"


#define INPUT_BUFFER_SIZE 100

void play_game(int fd, bool host)
{	
	#define DIMENSIONS 4 

	static NAC_GLYPH board[DIMENSIONS * DIMENSIONS];
	static char buffer[INPUT_BUFFER_SIZE] = { '\0' };
	static char buffer_for_processing[INPUT_BUFFER_SIZE] = { '\0' };
	static int buffer_size = 0;
	bool cross_turn = true;
	NAC_STATE state = {
		.dimensions = DIMENSIONS,
		.length = DIMENSIONS * DIMENSIONS,
		.board = board
	};

	NAC_GAME_RESULT game_result = NAC_NOT_OVER;
	NAC_MOVE_RESULT move_result = NAC_MOVE_INVALID;
	size_t target_index = 0;

	printf("%s\n", host ? "Hosting game" : "Joining game");
	do {
		display_game((const NAC_STATE *)&state);

		do {
			// If we are local, input is always local.
			// If we are online, we wait when it is not our turn.
			if (fd == 0 || (host && cross_turn) ||
			    (!host && !cross_turn)) {
				display_prompt(cross_turn);
				if (!(buffer_size =
					      poll_input(fd, buffer,
							 INPUT_BUFFER_SIZE))) {
					continue;
				}
				// We are expecting the next move from the network.
			} else {
				printf("Waiting for peer's turn...\n");
				if (!(buffer_size =
					      read_network_line(fd, buffer,
								INPUT_BUFFER_SIZE)))
				{
					printf("Peer disconnected\n");
					return;
				}
			}


			memcpy(buffer_for_processing, buffer,
			       INPUT_BUFFER_SIZE);
			if (!parse_move(buffer_for_processing, &target_index, state.dimensions)) {
				printf("Bad input, try again\n");
				continue;
			}
		} while ((move_result =
				  NAC_make_move(&state, target_index,
						cross_turn ? NAC_CROSS : NAC_NOUGHT)) ==
			 NAC_MOVE_INVALID);

		// Whenever we deem a move successful we can send it to the peer if they exist.
		if (fd != 0) {
			write_network_line(fd, buffer, buffer_size);
		}

		cross_turn = !cross_turn;
	} while ((game_result = NAC_game_status((const NAC_STATE *)&state)) ==
		 NAC_NOT_OVER);

	display_game((const NAC_STATE *)&state);
	display_game_result(game_result);
}

bool ask_yn(const char *prompt)
{
	static char answer_buffer[INPUT_BUFFER_SIZE] = { '\0' };
	do {
		printf("%s \"y/n\" > ", prompt);
		if (!poll_input(0, answer_buffer, INPUT_BUFFER_SIZE)) {
			continue;
		}
		char result = parse_yn(answer_buffer);
		switch (result) {
		case 'n':
			return false;
		case 'y':
			return true;
			break;
		default:
			printf("Invalid answer, please try again.\n");
		}
	} while (true);
}

// Returns file descriptor.
int online(bool *host)
{
	static char answer_buffer[INPUT_BUFFER_SIZE] = { '\0' };
	const char *port = "12345";
	static int fd = 0;

	if (ask_yn("Host server?")) {
		fd = host_server(port);
		if (fd > 0) {
			return fd;
		}
	}

	do {
		printf("Address? > ");

		if (!poll_input(0, answer_buffer, INPUT_BUFFER_SIZE)) {
			continue;
		}

		fd = connect_to_sever(answer_buffer, port);
	} while (fd <= 0);

	*host = false;

	return fd;
}

int main()
{
	do {
		static int fd = 0;
		bool host = true;
		if (ask_yn("Online game?")) {
			fd = online(&host);
		}

		if (fd > 0) {
			play_game(fd, host);
		} else {
			play_game(fd, host);
		}

		if (!ask_yn("Play again?")) {
			break;
		}
	} while (true);

	return 0;
}
