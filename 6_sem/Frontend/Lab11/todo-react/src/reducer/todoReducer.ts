import type { Todo, Action } from '../types/types';

export function todoReducer(state: Todo[], action: Action): Todo[] {
  switch (action.type) {
    case 'ADD_TODO':
      return [...state, { id: crypto.randomUUID(), name: action.payload, completed: false }];
    case 'REMOVE_TODO':
      return state.filter(todo => todo.id !== action.payload);
    case 'TOGGLE_TODO':
      return state.map(todo =>
        todo.id === action.payload ? { ...todo, completed: !todo.completed } : todo
      );
    case 'CLEAR_ALL':
      return [];
    case 'MOVE_UP': {
      const index = state.findIndex(todo => todo.id === action.payload);
      if (index > 0) {
        const newTodos = [...state];
        [newTodos[index - 1], newTodos[index]] = [newTodos[index], newTodos[index - 1]];
        return newTodos;
      }
      return state;
    }
    case 'MOVE_DOWN': {
      const index = state.findIndex(todo => todo.id === action.payload);
      if (index < state.length - 1) {
        const newTodos = [...state];
        [newTodos[index], newTodos[index + 1]] = [newTodos[index + 1], newTodos[index]];
        return newTodos;
      }
      return state;
    }
    default:
      return state;
  }
}
