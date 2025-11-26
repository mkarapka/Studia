import type { Todo, Action } from '../types/types';

type Props = {
  todo: Todo;
  dispatch: React.Dispatch<Action>;
  isFirst: boolean;
  isLast: boolean;
};

const TodoItem = ({ todo, dispatch, isFirst, isLast }: Props) => {
  return (
    <li className={`todo__container ${todo.completed ? 'todo__container--completed' : ''}`}>
      <div className="todo-element todo-name">{todo.name}</div>
      {!isFirst && (
        <button
          className="todo-element todo-button move-up"
          onClick={() => dispatch({ type: 'MOVE_UP', payload: todo.id })}
        >
          ↑
        </button>
      )}
      {!isLast && (
        <button
          className="todo-element todo-button move-down"
          onClick={() => dispatch({ type: 'MOVE_DOWN', payload: todo.id })}
        >
          ↓
        </button>
      )}
      <button
        className="todo-element todo-button"
        onClick={() => dispatch({ type: 'TOGGLE_TODO', payload: todo.id })}
      >
        {todo.completed ? 'Revert' : 'Done'}
      </button>
      <button
        className="todo-element todo-button"
        onClick={() => dispatch({ type: 'REMOVE_TODO', payload: todo.id })}
      >
        Remove
      </button>
    </li>
  );
};

export default TodoItem;
