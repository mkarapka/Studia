import type { Todo, Action } from '../types/types';
import TodoItem from './TodoItem';

type Props = {
  todos: Todo[];
  dispatch: React.Dispatch<Action>;
};

const TodoList = ({ todos, dispatch }: Props) => {
  return (
    <ul className="todos__list">
      {todos.map((todo, index) => (
        <TodoItem key={todo.id} todo={todo} dispatch={dispatch} 
        isFirst={index === 0} isLast={index === todos.length - 1} />
      ))}
    </ul>
  );
};

export default TodoList;
