#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import sys
from chess_engine import Chess, AI

WHITE = 1
BLACK = 0

class MAIN(object):
    def __init__(self):
        self.game = Chess()
        self.ai = AI()
        self.my_player = BLACK
        self.ai.update_main_player(self.my_player)
        self.say('RDY')

    def reset(self):
        self.game.reset()
        self.my_player = BLACK
        self.ai.update_main_player(self.my_player)
        self.say('RDY')

    def say(self, what):
        sys.stdout.write(what)
        sys.stdout.write('\n')
        sys.stdout.flush()

    def hear(self):
        line = sys.stdin.readline().split()
        return line[0], line[1:]

    def loop(self):
        while True:
            cmd, args = self.hear()
            if cmd == 'HEDID':
                unused_move_timeout, unused_game_timeout = args[:2]
                move = args[2]

                self.game.make_move(move)
            elif cmd == 'ONEMORE':
                self.reset()
                continue
            elif cmd == 'BYE':
                break
            else:
                assert cmd == 'UGO'
                self.my_player = WHITE
                self.ai.update_main_player(self.my_player)

            move = self.ai.get_best_move(self.game)
            self.game.make_move(move)

            self.say('IDO ' + move)

if __name__ == '__main__':
    main = MAIN()
    main.loop()
