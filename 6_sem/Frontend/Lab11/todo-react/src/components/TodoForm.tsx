import { useState } from 'react';
import type { Action } from '../types/types';

type Props = {
  dispatch: React.Dispatch<Action>;
};

const TodoForm = ({ dispatch }: Props) => {
  const [name, setName] = useState('');

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    if (name.trim() !== '') {
      dispatch({ type: 'ADD_TODO', payload: name });
      setName('');
    }
  };

  return (
    <form onSubmit={handleSubmit} className="add-item__container">
      <input
        type="text"
        name="todo-name"
        placeholder="What's on your mind?"
        value={name}
        onChange={(e) => setName(e.target.value)}
        required
        className="add-item__element add-item__input"
      />
      <button type="submit" className="add-item__element add-item__submit">
        Add
      </button>
    </form>
  );
};

export default TodoForm;
