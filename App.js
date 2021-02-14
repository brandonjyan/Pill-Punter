import { StatusBar } from 'expo-status-bar';
import React from 'react';
import { StyleSheet, SafeAreaView, Text, View, Image, TouchableOpacity } from 'react-native';

export default function App() {
  return (
    <SafeAreaView style={styles.container}>
      <Image 
        style={styles.logoContainer}
        source={require('./assets/Logo.png')}
    />
      <Image 
        style={styles.grandmaContainer}
        source={require('./assets/Grandma.png')}
    />
      <Text style={styles.titleText}>Too many pills?</Text>
      <Text style={styles.baseText}>Keep track of your medication.</Text>
      <TouchableOpacity>
        <Image
          style={styles.buttonContainer}
          source={require('./assets/Button.png')}
        />
      </TouchableOpacity>
      
      <StatusBar style="auto" />
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    flexDirection: "column",
    backgroundColor: '#fff',
    alignItems: 'center',
  },
  logoContainer: {
    width: 200,
    height: 100,
    resizeMode: "contain",
  },
  grandmaContainer: {
    width: 350,
    height: 350,
    resizeMode: "contain",
    borderRadius: 5,
    top: 30,
  },
  titleText: {
    fontFamily: 'Helvetica',
    fontStyle: 'normal',
    fontWeight: 'bold',
    fontSize: 30,
    top: 70,

    color: '#3F414E'
  },
  baseText: {
    fontFamily: 'Helvetica',
    fontStyle: 'normal',
    fontWeight: 'normal',
    fontSize: 16,
    top: 90,
    color: '#A1A4B2'
  },
  buttonContainer: {
    width: 300,
    height: 300,
    resizeMode: "contain",
    borderRadius: 5,
    top: 50
  }


});