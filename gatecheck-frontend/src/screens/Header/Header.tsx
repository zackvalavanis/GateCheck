import { Link } from "react-router"
import "./Header.css"
import airplane from '../../../public/airplane.svg'

export function Header() {
  return (
    <header className="header">
      <img src={airplane} alt="GateCheck"></img>
      <nav>
        <Link to='./'>Home</Link>
        <Link to='./airport_sim'>Airport Simulator</Link>
      </nav>
    </header>
  )
}