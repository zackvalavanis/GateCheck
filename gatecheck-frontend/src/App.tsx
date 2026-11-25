import './App.css'
import { BrowserRouter, Routes, Route } from 'react-router'
import { HomePage } from './screens/HomePage/HomePage'
import { Header } from './screens/Header/Header'
import { Footer } from './screens/Footer/Footer'

function App() {
  return (
    <BrowserRouter>
      <div className='app-layout'>
        <Header />
        <main className='app-main'>
          <Routes>
            <Route path='/' element={<HomePage />} />
          </Routes>
        </main>
        <Footer />
      </div>
    </BrowserRouter>
  )
}

export default App
