const form = document.getElementById('add-todo-form');
const input = form.querySelector('input[name="todo-name"]');
const todoList = document.getElementById('todo-list');
const clearButton = document.getElementById('todos-clear');
const countSpan = document.getElementById('count');

let todos = [];

function updateCount() {
  const remaining = todos.filter(todo => !todo.completed).length;
  countSpan.textContent = remaining;
}

function render() {
  todoList.innerHTML = '';

  todos.forEach((todo, index) => {
    const li = document.createElement('li');
    li.className = 'todo__container';
    if (todo.completed) {
      li.classList.add('todo__container--completed');
    }

    const nameDiv = document.createElement('div');
    nameDiv.className = 'todo-element todo-name';
    nameDiv.textContent = todo.name;
    li.appendChild(nameDiv);

    const moveUpBtn = document.createElement('button');
    moveUpBtn.className = 'todo-element todo-button move-up';
    moveUpBtn.textContent = '↑';
    moveUpBtn.addEventListener('click', () => {
      if (index > 0) {
        [todos[index - 1], todos[index]] = [todos[index], todos[index - 1]];
        render();
      }
    });
    li.appendChild(moveUpBtn);

    const moveDownBtn = document.createElement('button');
    moveDownBtn.className = 'todo-element todo-button move-down';
    moveDownBtn.textContent = '↓';
    moveDownBtn.addEventListener('click', () => {
      if (index < todos.length - 1) {
        [todos[index], todos[index + 1]] = [todos[index + 1], todos[index]];
        render();
      }
    });
    li.appendChild(moveDownBtn);

    const toggleBtn = document.createElement('button');
    toggleBtn.className = 'todo-element todo-button';
    toggleBtn.textContent = todo.completed ? 'Revert' : 'Done';
    toggleBtn.addEventListener('click', () => {
      todo.completed = !todo.completed;
      render();
    });
    li.appendChild(toggleBtn);

    const removeBtn = document.createElement('button');
    removeBtn.className = 'todo-element todo-button';
    removeBtn.textContent = 'Remove';
    removeBtn.addEventListener('click', () => {
      todos.splice(index, 1);
      render();
    });
    li.appendChild(removeBtn);

    todoList.appendChild(li);
  });

  updateCount();
}

form.addEventListener('submit', (e) => {
  e.preventDefault();
  const name = input.value.trim();
  if (name !== '') {
    todos.push({ name, completed: false });
    input.value = '';
    render();
  }
});

clearButton.addEventListener('click', () => {
  todos = [];
  render();
});

render(); // Initial render
