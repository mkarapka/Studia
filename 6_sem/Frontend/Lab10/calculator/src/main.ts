import { Calculator } from './calculator'

const calculator = new Calculator('display')

document.querySelectorAll('.btn').forEach((btn) => {
  const button = btn as HTMLButtonElement

  const value = button.dataset.value
  if (value !== undefined) {
    button.addEventListener('click', () => calculator.append(value))
  }
})

document.getElementById('clear')!.addEventListener('click', () => {
  calculator.clear()
})

document.getElementById('backspace')!.addEventListener('click', () => {
  calculator.backspace()
})

document.getElementById('equals')!.addEventListener('click', () => {
  calculator.calculate()
})
