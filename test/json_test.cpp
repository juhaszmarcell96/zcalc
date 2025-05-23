/*
 * Copyright (C) 2025 Marcell Juhasz
 *
 * This software is licensed under a non-commercial license.
 * Non-commercial use (personal, academic, research) is allowed for free.
 * Commercial use requires a paid license.
 * Hosting as a service is prohibited without explicit permission.
 *
 * See LICENSE for details or contact marcell.juhasz96@gmail.com.
 */

#include <gtest/gtest.h>

#include <zcalc/json/element.hpp>
#include <zcalc/json/parser.hpp>

TEST(JsonTest, JsonPrintTest) {
    zcalc::json::Element obj = zcalc::json::Object {
        {"name", "John"},
        {"age", 30},
        {"is_student", false},
        {"scores", zcalc::json::Array{85.5, 90.0, 78.2}}
    };
    
    std::cout << obj << std::endl;
}

TEST(JsonTest, JsonParseTest) {
    std::string json_text = R"(
        {
            "name": "John Doe",
            "age": 30,
            "isEmployed": true,
            "address": {
                "street": "123 Main St",
                "city": "New York"
            },
            "skills": ["C++", "Python", "Embedded Systems"],
            "projects": [
                { "name": "Project A", "year": 2021 },
                { "name": "Project B", "year": 2022 }
            ],
            "nullableField": null
        }
    )";

    zcalc::json::JsonParser parser { json_text };
    const auto json = parser.parse();

    // check root type
    ASSERT_TRUE(json.is_object());

    // check simple fields
    ASSERT_TRUE(json.as_object().at("name").is_string());
    ASSERT_EQ(json.as_object().at("name").as_string(), "John Doe");

    ASSERT_TRUE(json.as_object().at("age").is_number());
    ASSERT_EQ(json.as_object().at("age").as_number(), 30);

    ASSERT_TRUE(json.as_object().at("isEmployed").is_bool());
    ASSERT_EQ(json.as_object().at("isEmployed").as_bool(), true);

    ASSERT_TRUE(json.as_object().at("nullableField").is_null());

    // check nested object
    ASSERT_TRUE(json.as_object().at("address").is_object());
    const auto& address = json.as_object().at("address").as_object();
    ASSERT_EQ(address.at("street").as_string(), "123 Main St");
    ASSERT_EQ(address.at("city").as_string(), "New York");

    // check array
    ASSERT_TRUE(json.as_object().at("skills").is_array());
    const auto& skills = json.as_object().at("skills").as_array();
    ASSERT_EQ(skills.size(), 3);
    ASSERT_EQ(skills[0].as_string(), "C++");
    ASSERT_EQ(skills[1].as_string(), "Python");
    ASSERT_EQ(skills[2].as_string(), "Embedded Systems");

    // check array of objects
    ASSERT_TRUE(json.as_object().at("projects").is_array());
    const auto& projects = json.as_object().at("projects").as_array();
    ASSERT_EQ(projects.size(), 2);
    ASSERT_EQ(projects[0].as_object().at("name").as_string(), "Project A");
    ASSERT_EQ(projects[0].as_object().at("year").as_number(), 2021);
    ASSERT_EQ(projects[1].as_object().at("name").as_string(), "Project B");
    ASSERT_EQ(projects[1].as_object().at("year").as_number(), 2022);
}

TEST(JsonTest, JsonParseNestedTest) {
    std::string json_text = R"(
        {
            "name": "John Doe",
            "age": 30,
            "isEmployed": true,
            "address": {
                "street": "123 Main St",
                "city": "New York",
                "geo": {
                    "lat": 40.7128,
                    "lng": -74.0060
                }
            },
            "contacts": {
                "email": "john.doe@example.com",
                "phoneNumbers": [
                    { "type": "home", "number": "123-4567" },
                    { "type": "work", "number": "987-6543" }
                ]
            },
            "skills": ["C++", "Python", "Embedded Systems"],
            "projects": [
                { "name": "Project A", "year": 2021, "details": { "budget": 10000, "teamSize": 5 } },
                { "name": "Project B", "year": 2022, "details": { "budget": 20000, "teamSize": 8 } }
            ],
            "nullableField": null
        }
    )";

    zcalc::json::JsonParser parser { json_text };
    const auto json = parser.parse();

    // check root type
    ASSERT_TRUE(json.is_object());

    // check simple fields
    ASSERT_TRUE(json.as_object().at("name").is_string());
    ASSERT_EQ(json.as_object().at("name").as_string(), "John Doe");

    ASSERT_TRUE(json.as_object().at("age").is_number());
    ASSERT_EQ(json.as_object().at("age").as_number(), 30);

    ASSERT_TRUE(json.as_object().at("isEmployed").is_bool());
    ASSERT_EQ(json.as_object().at("isEmployed").as_bool(), true);

    ASSERT_TRUE(json.as_object().at("nullableField").is_null());

    // check nested object
    ASSERT_TRUE(json.as_object().at("address").is_object());
    const auto& address = json.as_object().at("address").as_object();
    ASSERT_EQ(address.at("street").as_string(), "123 Main St");
    ASSERT_EQ(address.at("city").as_string(), "New York");
    ASSERT_TRUE(address.at("geo").is_object());
    ASSERT_EQ(address.at("geo").as_object().at("lat").as_number(), 40.7128);
    ASSERT_EQ(address.at("geo").as_object().at("lng").as_number(), -74.0060);

    // check nested objects in contacts
    ASSERT_TRUE(json.as_object().at("contacts").is_object());
    const auto& contacts = json.as_object().at("contacts").as_object();
    ASSERT_EQ(contacts.at("email").as_string(), "john.doe@example.com");
    ASSERT_TRUE(contacts.at("phoneNumbers").is_array());
    const auto& phoneNumbers = contacts.at("phoneNumbers").as_array();
    ASSERT_EQ(phoneNumbers.size(), 2);
    ASSERT_EQ(phoneNumbers[0].as_object().at("type").as_string(), "home");
    ASSERT_EQ(phoneNumbers[0].as_object().at("number").as_string(), "123-4567");
    ASSERT_EQ(phoneNumbers[1].as_object().at("type").as_string(), "work");
    ASSERT_EQ(phoneNumbers[1].as_object().at("number").as_string(), "987-6543");

    // check array
    ASSERT_TRUE(json.as_object().at("skills").is_array());
    const auto& skills = json.as_object().at("skills").as_array();
    ASSERT_EQ(skills.size(), 3);
    ASSERT_EQ(skills[0].as_string(), "C++");
    ASSERT_EQ(skills[1].as_string(), "Python");
    ASSERT_EQ(skills[2].as_string(), "Embedded Systems");

    // check array of objects with nested data
    ASSERT_TRUE(json.as_object().at("projects").is_array());
    const auto& projects = json.as_object().at("projects").as_array();
    ASSERT_EQ(projects.size(), 2);
    ASSERT_EQ(projects[0].as_object().at("name").as_string(), "Project A");
    ASSERT_EQ(projects[0].as_object().at("year").as_number(), 2021);
    ASSERT_EQ(projects[0].as_object().at("details").as_object().at("budget").as_number(), 10000);
    ASSERT_EQ(projects[0].as_object().at("details").as_object().at("teamSize").as_number(), 5);
    ASSERT_EQ(projects[1].as_object().at("name").as_string(), "Project B");
    ASSERT_EQ(projects[1].as_object().at("year").as_number(), 2022);
    ASSERT_EQ(projects[1].as_object().at("details").as_object().at("budget").as_number(), 20000);
    ASSERT_EQ(projects[1].as_object().at("details").as_object().at("teamSize").as_number(), 8);
}

TEST(JsonTest, JsonParseNetworkTest) {
    std::string json_text = R"(
        {
            "num_nodes": 3,
            "components": [
                {
                    "id": "0",
                    "type": "resistor",
                    "value": 500,
                    "node_0": 2,
                    "node_1": 0
                },
                {
                    "id": "1",
                    "type": "resistor",
                    "value": 0.5,
                    "unit": "k",
                    "node_0": 1,
                    "node_1": 2
                },
                {
                    "type": "vsource",
                    "value": 1,
                    "frequency": 5000,
                    "phase": 1.1586,
                    "node_0": 1,
                    "node_1": 0
                }
            ]
        }
    )";

    zcalc::json::JsonParser parser { json_text };
    const auto json = parser.parse();

    // check root type
    ASSERT_TRUE(json.is_object());

    // check simple fields
    ASSERT_TRUE(json.as_object().at("num_nodes").is_number());
    ASSERT_EQ(json.as_object().at("num_nodes").as_number(), 3);

    // check array of objects
    ASSERT_TRUE(json.as_object().at("components").is_array());
    const auto& components = json.as_object().at("components").as_array();
    ASSERT_EQ(components.size(), 3);

    // check first component
    ASSERT_EQ(components[0].as_object().at("id").as_string(), "0");
    ASSERT_EQ(components[0].as_object().at("type").as_string(), "resistor");
    ASSERT_EQ(components[0].as_object().at("value").as_number(), 500);
    ASSERT_EQ(components[0].as_object().at("node_0").as_number(), 2);
    ASSERT_EQ(components[0].as_object().at("node_1").as_number(), 0);

    // check second component
    ASSERT_EQ(components[1].as_object().at("id").as_string(), "1");
    ASSERT_EQ(components[1].as_object().at("type").as_string(), "resistor");
    ASSERT_EQ(components[1].as_object().at("value").as_number(), 0.5);
    ASSERT_EQ(components[1].as_object().at("unit").as_string(), "k");
    ASSERT_EQ(components[1].as_object().at("node_0").as_number(), 1);
    ASSERT_EQ(components[1].as_object().at("node_1").as_number(), 2);

    // check third component
    ASSERT_EQ(components[2].as_object().at("type").as_string(), "vsource");
    ASSERT_EQ(components[2].as_object().at("value").as_number(), 1);
    ASSERT_EQ(components[2].as_object().at("frequency").as_number(), 5000);
    ASSERT_EQ(components[2].as_object().at("phase").as_number(), 1.1586);
    ASSERT_EQ(components[2].as_object().at("node_0").as_number(), 1);
    ASSERT_EQ(components[2].as_object().at("node_1").as_number(), 0);
}