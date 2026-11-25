import './App.css'
import { BrowserRouter, Routes, Route } from 'react-router'
import { HomePage } from './screens/HomePage/HomePage'
import { Header } from './screens/Header/Header'
import { Footer } from './screens/Footer/Footer'
import { AirportSim } from './screens/AirportSim/airportsim'

function App() {
  return (
    <BrowserRouter>
      <div className='app-layout'>
        <Header />
        <main className='app-main'>
          <Routes>
            <Route path='/' element={<HomePage />} />
            <Route path='/airport_sim' element={<AirportSim />}></Route>
          </Routes>
        </main>
        <Footer />
      </div>
    </BrowserRouter>
  )
}

export default App
