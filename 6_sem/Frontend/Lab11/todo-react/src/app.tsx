import { useReducer } from 'react';
import { todoReducer } from './reducer/todoReducer';
import Header from './components/Header';
import TodoForm from './components/TodoForm';
import TodoList from './components/TodoList';

function App() {
  const [todos, dispatch] = useReducer(todoReducer, []);

  return (
    <div className="body__wrapper">
      <header className="header__wrapper">
        <h1>Hello, Mikołaj!</h1>
      </header>
      <main className="main">
        <section>
          <TodoForm dispatch={dispatch} />
        </section>
        <section className="todos__container">
          <Header todos={todos} dispatch={dispatch} />
          <TodoList todos={todos} dispatch={dispatch} />
        </section>
      </main>
    </div>
  );
}

export default App;
