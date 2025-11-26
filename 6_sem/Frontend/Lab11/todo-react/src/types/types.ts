export interface Todo {
  id: string;
  name: string;
  completed: boolean;
}

export type Action =
  | { type: 'ADD_TODO'; payload: string }
  | { type: 'REMOVE_TODO'; payload: string }
  | { type: 'TOGGLE_TODO'; payload: string }
  | { type: 'CLEAR_ALL' }
  | { type: 'MOVE_UP'; payload: string }
  | { type: 'MOVE_DOWN'; payload: string };
