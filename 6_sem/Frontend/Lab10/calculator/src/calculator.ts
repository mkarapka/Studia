import { evaluate } from 'mathjs'

export class Calculator {
  private displayElement: HTMLElement
  private expression: string

  constructor(displayElementId: string) {
    this.displayElement = document.getElementById(displayElementId)!
    this.expression = ''
  }

  public append(value: string) {
    this.expression += value.replace(',', '.')
    this.updateDisplay()
  }

  public clear() {
    this.expression = ''
    this.updateDisplay()
  }

  public backspace() {
    this.expression = this.expression.slice(0, -1)
    this.updateDisplay()
  }

  public calculate() {
    try {
      const result = evaluate(this.expression)
      this.expression = result.toString()
    } catch {
      this.expression = 'Error'
    }
    this.updateDisplay()
  }

  private updateDisplay() {
    this.displayElement.innerText = this.expression || '0'
  }
}
