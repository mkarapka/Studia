import type { Todo, Action } from '../types/types';

type Props = {
  todos: Todo[];
  dispatch: React.Dispatch<Action>;
};

const Header = ({ todos, dispatch }: Props) => {
  const remaining = todos.filter(todo => !todo.completed).length;

  return (
    <header className="todos-header__container">
      <h2>
        Todo List (<span>{remaining}</span> remaining)
        <button
          onClick={() => dispatch({ type: 'CLEAR_ALL' })}
          className="todos-clear"
        >
          Clear all
        </button>
      </h2>
    </header>
  );
};

export default Header;
